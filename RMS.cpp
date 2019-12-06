#include "RMS.h"

using namespace std;
using namespace Eigen;
using namespace cv;

int psi(double t) {
	if (t < 0 || t >= 1) return 0;
	else return (t < 1 / 2) ? 1 : -1;
}

int phi(double t) {
	return (t < 0 || t >= 1) ? 0 : 1;
}

int psi_s_k(double t, int s, int k) {
	return psi(pow(2, s) * t - k);
};

int phi_s_k(double t, int s, int k) {
	return phi(pow(2, s) * t - k);
};

Matrix2i haar(int s, int kx, int ky, double x, double y) {
	MatrixXi m(2, 2);
	int m00 = pow(2, s) * phi_s_k(x, s, kx) * phi_s_k(y, s, ky);
	int m01 = pow(2, s) * phi_s_k(x, s, kx) * psi_s_k(y, s, ky);
	int m10 = pow(2, s) * psi_s_k(x, s, kx) * phi_s_k(y, s, ky);
	int m11 = pow(2, s) * psi_s_k(x, s, kx) * psi_s_k(y, s, ky);
	m << m00, m01,
		m10, m11;
	return m;
};

Point2f normalize(Point2f p, int wh) {
	return Point2f(p.x / (float)wh, p.y / (float)wh);
}

Bezigon normalize(Bezigon B, int wh) {
	Eigen::MatrixXd Bx = B.Bx;
	Eigen::MatrixXd By = B.By;
	Point2f new_point;
	for (int jj = 0; jj < Bx.rows(); jj++) {
		new_point = normalize(Point2f(Bx.row(jj)[0], By.row(jj)[0]), wh);
		Bx.row(jj)[0] = new_point.x;
		By.row(jj)[0] = new_point.y;
		new_point = normalize(Point2f(Bx.row(jj)[1], By.row(jj)[1]), wh);
		Bx.row(jj)[1] = new_point.x;
		By.row(jj)[1] = new_point.y;
		new_point = normalize(Point2f(Bx.row(jj)[2], By.row(jj)[2]), wh);
		Bx.row(jj)[2] = new_point.x;
		By.row(jj)[2] = new_point.y;
	}
	return Bezigon(Bx, By);
}

vector<Bezier> clip(Bezier bez, int left, int right, int bottom, int top) {
	Point2f A = -bez.control_points[0] + 3 * bez.control_points[1] - 3 * bez.control_points[2] + bez.control_points[3];
	Point2f B = 3 * bez.control_points[0] - 6 * bez.control_points[1] + 3 * bez.control_points[2];
	Point2f C = -3 * bez.control_points[0] + 3 * bez.control_points[1];
	Point2f D = bez.control_points[0];

	vector<double> ts;
	ts.push_back(0.);
	vector<double> roots = get_roots(A.x, B.x, C.x, D.x - left);
	ts.insert(ts.end(), roots.begin(), roots.end());
	roots = get_roots(A.x, B.x, C.x, D.x - right);
	ts.insert(ts.end(), roots.begin(), roots.end());
	roots = get_roots(A.y, B.y, C.y, D.y - bottom);
	ts.insert(ts.end(), roots.begin(), roots.end());
	roots = get_roots(A.y, B.y, C.y, D.y - top);
	ts.insert(ts.end(), roots.begin(), roots.end());
	ts.push_back(1.);

	for (auto it = ts.begin(); it != ts.end(); ++it) {
		Point p_root = bez.cubic_interpolation(*it);
		if (!(0 <= *it <= 1 && left <= p_root.x && p_root.x <= right && top <= p_root.y && p_root.y <= bottom)) ts.erase(it);
	}
	sort(ts.begin(), ts.end());
	unique(ts.begin(), ts.end());

	vector<Bezier> boundary_bez;
	for (int ii = 1; ii < ts.size(); ii++) {
		Point2f middle = bez.cubic_interpolation(0.5 * (ts[ii - 1] + ts[ii]));
		if (left <= middle.x && middle.x <= right && top <= middle.y && middle.y <= bottom) {
			boundary_bez.push_back(bez.subdivide(ts[ii - 1])[1].subdivide(ts[ii])[0]);
		}
	}

	return boundary_bez;
}

array<Point2f, 2> get_KL(Bezier bez) {
	double Kx = 0, Ky = 0, Lx = 0, Ly = 0;
	vector<Bezier> boundary_bez = clip(bez, 0, 1, 1, 0);
	for (Bezier bbez : boundary_bez) {
		Point2f p3 = bbez.control_points[0];
		Point2f p2 = bbez.control_points[1];
		Point2f p1 = bbez.control_points[2];
		Point2f p0 = bbez.control_points[3];
		Kx += 1. / 4 * (p0.y - p3.y);
		Ky += 1. / 4 * (p3.x - p0.x);
		Lx += 1. / 80 * (6 * p2.y * p3.x + 3 * p1.y * (p2.x + p3.x)
			+ p0.y * (6 * p1.x + 3 * p2.x + p3.x)
			- 6 * p2.x * p3.y - 3 * p1.x * (p2.y + p3.y)
			- 10 * p3.x * p3.y
			+ p0.x * (10 * p0.y - 6 * p1.y - 3 * p2.y - p3.y));
		Ly += 1. / 80 * (6 * p2.y * p3.x + 3 * p1.y * (p2.x + p3.x)
			+ p0.y * (6 * p1.x + 3 * p2.x + p3.x)
			- 6 * p2.x * p3.y - 3 * p1.x * (p2.y + p3.y)
			+ 10 * p3.x * p3.y
			- p0.x * (10 * p0.y + 6 * p1.y + 3 * p2.y + p3.y));
	}
	return { Point2f(Kx,Ky),Point2f(Lx,Ly) };
}

Bezier transform(Bezier bez, Point Q, int ss, int kx, int ky) {
	Point2f p0 = bez.control_points[0];
	p0.x = pow(2, ss + 1) * p0.x - kx * 2 - Q.x;
	p0.x = pow(2, ss + 1) * p0.y - ky * 2 - Q.y;
	Point2f p1 = bez.control_points[1];
	p1.x = pow(2, ss + 1) * p1.x - kx * 2 - Q.x;
	p1.x = pow(2, ss + 1) * p1.y - ky * 2 - Q.y;
	Point2f p2 = bez.control_points[2];
	p2.x = pow(2, ss + 1) * p2.x - kx * 2 - Q.x;
	p2.x = pow(2, ss + 1) * p2.y - ky * 2 - Q.y;
	Point2f p3 = bez.control_points[3];
	p3.x = pow(2, ss + 1) * p3.x - kx * 2 - Q.x;
	p3.x = pow(2, ss + 1) * p3.y - ky * 2 - Q.y;
	return Bezier(p0, p1, p2, p3);
}

array<double, 3> get_coef(Bezigon B, int jj, int ss, int kx, int ky) {
	Point Q_00 = Point(0, 0);	Point Q_01 = Point(0, 1);
	Point Q_10 = Point(1, 0);	Point Q_11 = Point(1, 1);
	double c10 = 0, c01 = 0, c11 = 0;
	array < Point2f, 2 > KL_Q_00 = get_KL(transform(B.get_bezier(jj), Q_00, ss, kx, ky));
	array < Point2f, 2 > KL_Q_01 = get_KL(transform(B.get_bezier(jj), Q_01, ss, kx, ky));
	array < Point2f, 2 > KL_Q_10 = get_KL(transform(B.get_bezier(jj), Q_10, ss, kx, ky));
	array < Point2f, 2 > KL_Q_11 = get_KL(transform(B.get_bezier(jj), Q_11, ss, kx, ky));
	c10 += KL_Q_00[1].x + KL_Q_01[1].x + KL_Q_10[0].x
		- KL_Q_10[1].x + KL_Q_11[0].x - KL_Q_11[1].x;
	c01 += KL_Q_00[1].y + KL_Q_10[1].y + KL_Q_01[0].y
		- KL_Q_01[1].y + KL_Q_11[0].y - KL_Q_11[1].y;
	c11 += KL_Q_00[1].x - KL_Q_01[1].x + KL_Q_10[0].x
		- KL_Q_10[1].x - KL_Q_11[0].x + KL_Q_11[1].x;
	return { c01 , c10 , c11 };
}

double c_00(Bezier bez) {
	Point2f p0 = bez.control_points[0];
	Point2f p1 = bez.control_points[1];
	Point2f p2 = bez.control_points[2];
	Point2f p3 = bez.control_points[3];
	return 3.0 / 10.0 * det(p0, p1) + 3.0 / 20.0 * det(p1, p2) + 3.0 / 10.0 * det(p2, p3) + 3.0 / 20.0 * det(p0, p2) + 3.0 / 20.0 * det(p1, p3) + 1.0 / 20.0 * det(p0, p3);
}

double color(Bezigon B, int d, int N, map<array<int, 4>, array<double, 3>> coef_map, Point2f p) {
	double s = 0;
	for (int jj = 0; jj < N; jj++) {
		s += c_00(B.get_bezier(jj));
		for (int ss = 0; ss < d + 1; ss++) {
			for (int kx = 0; kx < pow(2, ss); kx++) {
				for (int ky = 0; ky < pow(2, ss); ky++) {
					array<double, 3> c_list = coef_map[{jj, ss, kx, ky}];
					Matrix2i psis = haar(ss, kx, ky, p.x, p.y);
					if (psis(0, 1) > 0) s += c_list[0];
					else if (psis(0, 1) < 0) s -= c_list[0];
					if (psis(1, 0) > 0) s += c_list[1];
					else if (psis(1, 0) < 0) s -= c_list[1];
					if (psis(1, 1) > 0) s += c_list[2];
					else if (psis(1, 1) < 0) s -= c_list[2];
				}
			}
		}
	}
	cout << s << endl;
	return s;
}

Image<Vec3b> get_rasterized_wavelet(VectorizationData vd, int d, int N, map<array<int, 4>, array<double, 3>> coef_map, int wh) {
	Vec3b white = { 255,255,255 };
	Vec3b black = { 0,0,0 };

	Vec3b raster_color = { 0,0,255 };

	Image<Vec3b> I_raster(vd.I.width(), vd.I.height());

	for (size_t xx = 0; xx < vd.I.width(); xx++) {
		for (size_t yy = 0; yy < vd.I.height(); yy++) {
			Point2f p = normalize(Point(xx, yy), wh);
			I_raster(xx, yy) = color(vd.B, d, N, coef_map, p) * raster_color;
			cout << endl;
			cout << I_raster(xx, yy) << endl;
		}
	};

	return I_raster;
}

void rms_wavelet(VectorizationData vd) {
	int N = vd.B.Bx.rows();
	int d = ceil(log2(max(vd.I.width(), vd.I.height()))) - 1;
	//int d = 5;
	int wh = pow(2, d + 1);

	map<array<int, 4>, array<double, 3>> coef_map;
	// key : jj,ss,kx,ky
	// value : c01 c10 c11
	for (int jj = 0; jj < N; jj++) { //iterate over bezier curves of the bezigon
		for (int ss = 0; ss < d + 1; ss++) { //iterate through scaling
			for (int kx = 0; kx < pow(2, ss); kx++) { //iterate through translation x
				for (int ky = 0; ky < pow(2, ss); ky++) { //iterate through translation y
					Bezigon B = normalize(vd.B, wh);
					coef_map[{jj, ss, kx, ky}] = get_coef(B, jj, ss, kx, ky);
					cout << "...";
				}
			}
		}
	}

	Image<Vec3b> I_raster = get_rasterized_wavelet(vd, d, N, coef_map, wh);
	imshow("Rasterized Image", I_raster);
}

bool is_interior(Point p, Bezigon B) {
	int count = 0;
	Bezier bez;
	double c0, c1, c2, c3;
	for (size_t jj = 0; jj < B.Bx.rows(); jj++) {
		bez = B.get_bezier(jj);
		c3 = -bez.control_points[0].y + 3 * bez.control_points[1].y - 3 * bez.control_points[2].y + bez.control_points[3].y;
		c2 = 3 * bez.control_points[0].y - 6 * bez.control_points[1].y + 3 * bez.control_points[2].y;
		c1 = -3 * bez.control_points[0].y + 3 * bez.control_points[1].y;
		c0 = bez.control_points[0].y;
		vector<double> roots = get_roots(c3, c2, c1, c0 - p.y);
		unique(roots.begin(), roots.end());
		for (double root : roots) {
			if (root < 1.0 && root >= 0.0 && bez.cubic_interpolation(root).x < p.x) count++;
		}
	}
	return count % 2 == 1;
};

Image<cv::Vec3b> get_rasterized(VectorizationData vd) {
	Vec3b white = { 255,255,255 };
	Vec3b black = { 0,0,0 };

	Vec3f aux_color = { 0,0,0 };
	Vec3b color = { 0,0,255 };

	Image<Vec3b> I_int(vd.I.width(), vd.I.height());
	int count_int = 0;
	for (size_t xx = 0; xx < vd.I.width(); xx++) {
		for (size_t yy = 0; yy < vd.I.height(); yy++) {
			if (is_interior(Point(xx, yy), vd.B)) {
				I_int(xx, yy) = black;
				count_int++;
				aux_color += vd.I(xx, yy);
			}
			else {
				I_int(xx, yy) = white;
			}
		}
	};
	color = aux_color / count_int;
	for (size_t xx = 0; xx < vd.I.width(); xx++) {
		for (size_t yy = 0; yy < vd.I.height(); yy++) {
			if (I_int(xx, yy) == black) {
				I_int(xx, yy) = color;
			}
		}
	};
	return I_int;
}


void rms(VectorizationData vd) {
	Image<Vec3b> I_int = get_rasterized(vd);
	imshow("Rasterized Image", I_int);
}


//
//bool is_interior(Point p, MatrixXi curve) {
//	// first method to tell if a point is inside a curve (supposing the last point of the matrix is linked to the first one)
//	int count = 0;
//	int nb_points = curve.rows();
//	int min_y = curve.colwise().minCoeff()[1];
//	int max_y = curve.colwise().maxCoeff()[1];
//	if (min_y == p.y || max_y == p.y) return false; // to get rid of the corners and not count on the line
//	for (size_t ii = 0; ii < nb_points - 1; ii++) {
//		if ((curve.row(ii)[1] - p.y) * (curve.row(ii + 1)[1] - p.y) <= 0
//			&& (curve.row(ii + 1)[1] - p.y) != 0
//			&& curve.row(ii + 1)[0] < p.x
//			&& curve.row(ii)[0] < p.x) {
//			count++;
//		};
//	}
//	if ((curve.row(nb_points - 1)[1] - p.y) * (curve.row(0)[1] - p.y) <= 0
//		&& (curve.row(0)[1] - p.y) != 0
//		&& curve.row(0)[0] < p.x
//		&& curve.row(nb_points - 1)[0] < p.x) {
//		count++;
//	};
//	return count % 2 == 1;
//};
//
//
//Image<Vec3b> get_rasterized(VectorizationData vd) {
//	Vec3b white = { 255,255,255 };
//	Vec3b black = { 0,0,0 };
//
//	Vec3f aux_color = { 0,0,0 };
//	Vec3b color = { 0,0,255 };
//
//	Image<Vec3b> I_int(vd.I.width(), vd.I.height());
//	MatrixXi curve = vd.B->get_sample_points();
//	int count_int = 0;
//	for (size_t xx = 0; xx < vd.I.width(); xx++) {
//		for (size_t yy = 0; yy < vd.I.height(); yy++) {
//			if (is_interior(Point(xx, yy), curve)) {
//				I_int(xx, yy) = black;
//				count_int++;
//				aux_color += vd.I(xx, yy);
//			}
//			else {
//				I_int(xx, yy) = white;
//			}
//		}
//	};
//	color = aux_color / count_int;
//	for (size_t xx = 0; xx < vd.I.width(); xx++) {
//		for (size_t yy = 0; yy < vd.I.height(); yy++) {
//			if (I_int(xx, yy) == black) {
//				I_int(xx, yy) = color;
//			}
//		}
//	};
//
//	return I_int;
//
//}
//void show_rasterized(VectorizationData vd) {
//	Image<Vec3b> I_int = get_rasterized(vd);
//	imshow("Rasterized Image", I_int);
//}


