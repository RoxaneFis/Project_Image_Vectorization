#include "Entities.h"

using namespace cv;
using namespace std;
using namespace Eigen;

Bezier::Bezier() {
};

Bezier::Bezier(Point2d p0, Point2d p1, Point2d p2, Point2d p3) {
	control_points[0] = p0;	control_points[1] = p1;
	control_points[2] = p2;	control_points[3] = p3;
};

array<Bezier, 2> Bezier::subdivide(double t0) {
	Point2d p0 = control_points[0];
	Point2d p1 = barycenter(t0, p0, control_points[1]);
	Point2d paux = barycenter(t0, control_points[1], control_points[2]);
	Point2d p6 = control_points[3];
	Point2d p5 = barycenter(t0, control_points[2], p6);
	Point2d p2 = barycenter(t0, p1, paux);
	Point2d p4 = barycenter(t0, paux, p5);
	Point2d p3 = barycenter(t0, p2, p4);
	return { Bezier(p0,p1,p2,p3), Bezier(p3,p4,p5,p6) };
}

Point2d Bezier::cubic_interpolation(double t) {
	double s = 1 - t;
	return  s * s * s * control_points[0] + 3 * s * s * t * control_points[1] + 3 * s * t * t * control_points[2] + t * t * t * control_points[3];
}

Bezigon::Bezigon() {
}

Bezigon::Bezigon(MatrixXd _Bx, MatrixXd _By) {
	Bx = _Bx;
	By = _By;
	lo = get_arclength();
	C = Vec3b(255, 255, 255);
};

Bezigon::Bezigon(vector<Point> vp) {
	int nb_bezier = vp.size();
	Bx = MatrixXd(nb_bezier, 3);
	By = MatrixXd(nb_bezier, 3);
	C = Vec3b(255, 255, 255);
	Point2f tangent_next, tangent_prev;
	for (int jj = 1; jj < nb_bezier - 1; jj++) {
		tangent_next = vp[jj] + 0.33 * norm(vp[jj + 1] - vp[jj]) * (vp[jj + 1] - vp[jj - 1]) / norm(vp[jj + 1] - vp[jj - 1]);
		tangent_prev = vp[jj] + 0.33 * norm(vp[jj - 1] - vp[jj]) * (vp[jj - 1] - vp[jj + 1]) / norm(vp[jj - 1] - vp[jj + 1]);
		Bx.row(jj - 1)[2] = tangent_prev.x;
		Bx.row(jj)[0] = double(vp[jj].x);
		Bx.row(jj)[1] = tangent_next.x;
		By.row(jj - 1)[2] = tangent_prev.y;
		By.row(jj)[0] = double(vp[jj].y);
		By.row(jj)[1] = tangent_next.y;
	}
	tangent_next = vp[0] + 0.33 * norm(vp[1] - vp[0]) * (vp[1] - vp[nb_bezier - 1]) / norm(vp[1] - vp[nb_bezier - 1]);
	tangent_prev = vp[0] + 0.33 * norm(vp[nb_bezier - 1] - vp[0]) * (vp[nb_bezier - 1] - vp[1]) / norm(vp[1] - vp[nb_bezier - 1]);
	Bx.row(nb_bezier - 1)[2] = tangent_prev.x;
	Bx.row(0)[0] = double(vp[0].x);
	Bx.row(0)[1] = tangent_next.x;
	By.row(nb_bezier - 1)[2] = tangent_prev.y;
	By.row(0)[0] = double(vp[0].y);
	By.row(0)[1] = tangent_next.y;

	tangent_next = vp[nb_bezier - 1] + 0.33 * norm(vp[nb_bezier - 1] - vp[0]) * (vp[0] - vp[nb_bezier - 2]) / norm(vp[0] - vp[nb_bezier - 2]);
	tangent_prev = vp[nb_bezier - 1] + 0.33 * norm(vp[nb_bezier - 1] - vp[nb_bezier - 2]) * (vp[nb_bezier - 2] - vp[0]) / norm(vp[0] - vp[nb_bezier - 2]);
	Bx.row(nb_bezier - 2)[2] = tangent_prev.x;
	Bx.row(nb_bezier - 1)[0] = double(vp[nb_bezier - 1].x);
	Bx.row(nb_bezier - 1)[1] = tangent_next.x;
	By.row(nb_bezier - 2)[2] = tangent_prev.y;
	By.row(nb_bezier - 1)[0] = double(vp[nb_bezier - 1].y);
	By.row(nb_bezier - 1)[1] = tangent_next.y;
	lo = get_arclength();
}

void Bezigon::set_point_x(int j, int i, double coord_x) {
	Bx.row(j)[i] = coord_x;
};

void Bezigon::set_point_y(int j, int i, double coord_y) {
	By.row(j)[i] = coord_y;
};

Bezier Bezigon::get_bezier(int j) {
	Point2d p0 = Point2d(Bx.row(j)[0], By.row(j)[0]);
	Point2d p1 = Point2d(Bx.row(j)[1], By.row(j)[1]);
	Point2d p2 = Point2d(Bx.row(j)[2], By.row(j)[2]);
	Point2d p3 = (j != Bx.rows() - 1) ?
		Point2d(Bx.row(j + 1)[0], By.row(j + 1)[0]) : Point2d(Bx.row(0)[0], By.row(0)[0]);
	return Bezier(p0, p1, p2, p3);
};

Point2d Bezigon::get_pt(int j, int i = 0) {
	j = (j > 0) ? j % Bx.rows() : (-j) % (-Bx.rows());
	Point2d p0 = Point2d(Bx.row(j)[i], By.row(j)[i]);
	return Point2d(Bx.row(j)[i], By.row(j)[i]);

};

array< vector<double>, 2 > Bezigon::get_tangent(int point){
    Point2d p_precedent = (point != 0) ? get_pt(point-1, 2) : get_pt(Bx.rows()-1, 2);
	Point2d p_1 = (point != Bx.rows() - 1) ? get_pt(point, 0) : get_pt(0, 0);
	Point2d p_2 = (point != Bx.rows() - 1) ? get_pt(point, 1) : get_pt(0, 1);
	vector<double> a_j = {(p_1 - p_precedent).x, (p_1 - p_precedent).y};
	vector<double> b_j = { (p_2- p_1).x,(p_2- p_1).y };
	return {{a_j,b_j}};
	
	}




double Bezigon::get_arclength(int j) {
	Bezier bezier_j = get_bezier(j);
	double length = 0.0;
	Point2d previous_point = get_pt(j);
	Point2d actual_point;
	for (double t = 0.2; t <= 1.0; t += 0.2) {
		actual_point = bezier_j.cubic_interpolation(t);
		length += distance(actual_point, previous_point);
		previous_point = actual_point;
	}
	return length;
};

double Bezigon::get_arclength() {
	double length = 0.0;
	for (int jj = 0; jj < Bx.rows(); jj++) {
		length += get_arclength(jj);
	}
	return length;
};

void Bezigon::update(array<double, 10> vals_inp, int j) {
	if (j < Bx.rows() - 1) {
		set_point_x(j, 1, vals_inp[0]);
		set_point_x(j, 2, vals_inp[1]);
		set_point_x(j + 1, 0, vals_inp[2]);
		set_point_x(j + 1, 1, vals_inp[3]);
		set_point_x(j + 1, 2, vals_inp[4]);

		set_point_y(j, 1, vals_inp[5]);
		set_point_y(j, 2, vals_inp[6]);
		set_point_y(j + 1, 0, vals_inp[7]);
		set_point_y(j + 1, 1, vals_inp[8]);
		set_point_y(j + 1, 2, vals_inp[9]);
	}
	else {
		set_point_x(Bx.rows() - 1, 1, vals_inp[0]);
		set_point_x(Bx.rows() - 1, 2, vals_inp[1]);
		set_point_x(0, 0, vals_inp[2]);
		set_point_x(0, 1, vals_inp[3]);
		set_point_x(0, 2, vals_inp[4]);
		set_point_y(Bx.rows() - 1, 1, vals_inp[5]);
		set_point_y(Bx.rows() - 1, 2, vals_inp[6]);
		set_point_y(0, 0, vals_inp[7]);
		set_point_y(0, 1, vals_inp[8]);
		set_point_y(0, 2, vals_inp[9]);
	}
}

array<double, 10> Bezigon::input_propagation(int j) {
	Point2d p1 = get_pt(j, 1);
	Point2d p2 = get_pt(j, 2);
	Point2d p3 = (j != Bx.rows() - 1) ? get_pt(j+1, 0) : get_pt(0, 0);
	Point2d p4 = (j != Bx.rows() - 1) ? get_pt(j+1, 1) : get_pt(0, 1);
	Point2d p5 = (j != Bx.rows() - 1) ? get_pt(j+1, 2) : get_pt(0, 2);
	array<double, 10> x = { double(p1.x),double(p2.x),double(p3.x),double(p4.x),double(p5.x), double(p1.y),double(p2.y),double(p3.y),double(p4.y),double(p5.y) };
	return x;
}

void Bezigon::plot_curve(Image<Vec3b> I, std::string nom) {
	Bezier bezier_j;
	Image<Vec3b> I_copy ;
	I.copyTo(I_copy);
	for (int jj = 0; jj < Bx.rows(); jj++) {
		bezier_j = get_bezier(jj);
		for (double t = 0.0; t <= 1.0; t += 0.05) {
			Point2d m1 = bezier_j.cubic_interpolation(t);
			circle(I_copy, m1, 1, Scalar(0, 255, 0), 2);
			namedWindow(nom,WINDOW_NORMAL);
			resizeWindow(nom, 200, 200);
			imshow(nom, I_copy);
			waitKey(1);
		}
	}
}

VectorizationData::VectorizationData(Bezigon _B, Image<Vec3b> _I) {
	B = _B;
	I = _I;
}