#include "Entities.h"

using namespace cv;
using namespace std;
using namespace Eigen;

Bezier::Bezier() {
};

Bezier::Bezier(Point2f p0, Point2f p1, Point2f p2, Point2f p3) {
	control_points[0] = p0;	control_points[1] = p1;
	control_points[2] = p2;	control_points[3] = p3;
};

array<Bezier, 2> Bezier::subdivide(double t0) {
	Point2f p0 = control_points[0];
	Point2f p1 = barycenter(t0, p0, control_points[1]);
	Point2f paux = barycenter(t0, control_points[1], control_points[2]);
	Point2f p6 = control_points[3];
	Point2f p5 = barycenter(t0, control_points[2], p6);
	Point2f p2 = barycenter(t0, p1, paux);
	Point2f p4 = barycenter(t0, paux, p5);
	Point2f p3 = barycenter(t0, p2, p4);
	return { Bezier(p0,p1,p2,p3), Bezier(p3,p4,p5,p6) };
}

Point2f Bezier::cubic_interpolation(double t) {
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

Bezigon::Bezigon(vector<Point> vector_points) {
	int nb_bezier = vector_points.size();
	Bx = MatrixXd(nb_bezier, 3);
	By = MatrixXd(nb_bezier, 3);
	C = Vec3b(255, 255, 255);
	Point2f tangent1, tangent2;
	for (int jj = 0; jj < nb_bezier - 1; jj++) {
		tangent1 = barycenter(0.33, vector_points[jj], vector_points[jj + 1]);
		tangent2 = barycenter(0.66, vector_points[jj], vector_points[jj + 1]);
		Bx.row(jj) << double(vector_points[jj].x), tangent1.x, tangent2.x;
		By.row(jj) << double(vector_points[jj].y), tangent1.y, tangent2.y;
	}
	tangent1 = barycenter(0.33, vector_points[nb_bezier - 1], vector_points[0]);
	tangent2 = barycenter(0.66, vector_points[nb_bezier - 1], vector_points[0]);
	Bx.row(nb_bezier - 1) << double(vector_points[nb_bezier - 1].x), tangent1.x, tangent2.x;
	By.row(nb_bezier - 1) << double(vector_points[nb_bezier - 1].y), tangent1.y, tangent2.y;
	lo = get_arclength();
}

void Bezigon::set_point_x(int j, int i, double coord_x) {
	Bx.row(j)[i] = coord_x;
};

void Bezigon::set_point_y(int j, int i, double coord_y) {
	By.row(j)[i] = coord_y;
};

Bezier Bezigon::get_bezier(int j) {
	Point2f p0 = Point2f(Bx.row(j)[0], By.row(j)[0]);
	Point2f p1 = Point2f(Bx.row(j)[1], By.row(j)[1]);
	Point2f p2 = Point2f(Bx.row(j)[2], By.row(j)[2]);
	Point2f p3 = (j != Bx.rows() - 1) ?
		Point2f(Bx.row(j + 1)[0], By.row(j + 1)[0]) : Point2f(Bx.row(0)[0], By.row(0)[0]);
	return Bezier(p0, p1, p2, p3);
};

Point2f Bezigon::get_pt(int j, int i = 0) {
	Point2f p0 = Point2f(Bx.row(j)[i], By.row(j)[i]);
	return Point2f(Bx.row(j)[i], By.row(j)[i]);

};

array< vector<double>, 2 > Bezigon::get_tangent(int point){
    Point2f p_precedent = (point != 0) ? get_pt(point-1, 2) : get_pt(Bx.rows()-1, 2);
	Point2f p_1 = (point != Bx.rows() - 1) ? get_pt(point, 0) : get_pt(0, 0);
	Point2f p_2 = (point != Bx.rows() - 1) ? get_pt(point, 1) : get_pt(0, 1);
	vector<double> a_j = {(p_1 - p_precedent).x, (p_1 - p_precedent).y};
	vector<double> b_j = { (p_2- p_1).x,(p_2- p_1).y };
	return {{a_j,b_j}};
	
	}




double Bezigon::get_arclength(int j) {
	Bezier bezier_j = get_bezier(j);
	double length = 0.0;
	Point2f previous_point = get_pt(j);
	Point2f actual_point;
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
	Point2f p1 = get_pt(j, 1);
	Point2f p2 = get_pt(j, 2);
	Point2f p3 = (j != Bx.rows() - 1) ? get_pt(j+1, 0) : get_pt(0, 0);
	Point2f p4 = (j != Bx.rows() - 1) ? get_pt(j+1, 1) : get_pt(0, 1);
	Point2f p5 = (j != Bx.rows() - 1) ? get_pt(j+1, 2) : get_pt(0, 2);
	array<double, 10> x = { double(p1.x),double(p2.x),double(p3.x),double(p4.x),double(p5.x), double(p1.y),double(p2.y),double(p3.y),double(p4.y),double(p5.y) };
	return x;
}

void Bezigon::plot_curve(Image<Vec3b> I, std::string nom) {
	Bezier bezier_j;
	int v1  = rand() % 255;
	int v2  = rand() % 255;
	int v3  = rand() % 255;
	for (int jj = 0; jj < Bx.rows(); jj++) {
		bezier_j = get_bezier(jj);
		for (double t = 0.0; t <= 1.0; t += 0.05) {
			Point2f m1 = bezier_j.cubic_interpolation(t);
			circle(I, m1, 1, Scalar(v1, v2, v3), 2);
			imshow(nom, I);
			waitKey(1);
		}
	}
}

VectorizationData::VectorizationData(Bezigon _B, Image<Vec3b> _I) {
	B = _B;
	I = _I;
}