#include "Entities.h"

using namespace cv;
using namespace std;
using namespace Eigen;

//
// Bezier entity:
//

Bezier::Bezier(int N) {
	Nb_bezigons = N;
	By = new Eigen::MatrixXd(N, 3);
	Bx = new Eigen::MatrixXd(N, 3);
	By->setZero();
	Bx->setZero();
};

Bezier::Bezier(const MatrixXd& B_x, const MatrixXd& B_y) {
	Nb_bezigons = B_x.rows();
	By = new MatrixXd(Nb_bezigons, 3);
	Bx = new MatrixXd(Nb_bezigons, 3);
	*Bx = B_x;
	*By = B_y;
};


Bezier::Bezier(const std::vector<cv::Point>& vector_points) {
	int jj = 0;
	Nb_bezigons = vector_points.size();
	By = new MatrixXd(Nb_bezigons, 3);
	Bx = new MatrixXd(Nb_bezigons, 3);
	std::array<cv::Point, 2> tangent_points;
	for (int ii = 0; ii < Nb_bezigons - 1; ii++) {
		tangent_points = barycenters(0.3, vector_points[ii], vector_points[ii + 1]);
		Bx->row(ii) << double(vector_points[ii].x), tangent_points[0].x, tangent_points[1].x;
		By->row(ii) << double(vector_points[ii].y), tangent_points[0].y, tangent_points[1].y;
	}
	tangent_points = barycenters(0.3, vector_points[Nb_bezigons - 1], vector_points[0]);
	Bx->row(Nb_bezigons - 1) << double(vector_points[Nb_bezigons - 1].x), tangent_points[0].x, tangent_points[1].x;
	By->row(Nb_bezigons - 1) << double(vector_points[Nb_bezigons - 1].y), tangent_points[0].y, tangent_points[1].y;

}

std::array<std::vector<double>, 2> Bezier::get_tangents(int j) {
	//Returns left et right tangents of a point
	//FIXME : doesnt take first and last true points into account
	std::array<std::vector<double>, 2> tangents;
	vector<double> left_tangent(2);
	vector<double> right_tangent(2);
	if (j >= Nb_bezigons) {
		std::cout << "The index is too high. The point doesn't exist" << std::endl;
		return tangents;
	}
	if (j == 0) {
		//Make a loop 
		left_tangent = { get_ptx(j,0) - get_ptx(Nb_bezigons - 2,2),get_pty(j,0) - get_pty(Nb_bezigons - 2,2) };
		right_tangent = { get_ptx(j,2) - get_ptx(j,0),get_pty(j,2) - get_pty(j,0) };

	}
	else
	{
		left_tangent = { get_ptx(j,0) - get_ptx(j - 1,2),get_pty(j,0) - get_pty(j - 1,2) };
		right_tangent = { get_ptx(j,2) - get_ptx(j,0),get_pty(j,2) - get_pty(j,0) };
	}
	return { left_tangent, right_tangent };
}

float Bezier::arclength() {
	//Returns the arclegth of the Bezigon
	return 0.0;
};

int Bezier::nb_points() { return Nb_bezigons - 1; }

MatrixXd Bezier::intersection() {
	//Returns points that intersect // Maybe directly in Energy?
	MatrixXd inter;
	return inter;
};
void Bezier::set_point_x(int i, int j, double coord_x) {
	Bx->row(i)[j] = coord_x;
};
void Bezier::set_point_y(int i, int j, double coord_y) {
	By->row(i)[j] = coord_y;
};
double Bezier::get_ptx(int i, int j) {
	return Bx->row(i)[j];
};
double Bezier::get_pty(int i, int j) {
	return By->row(i)[j];
};
MatrixXd Bezier::get_Bx() {
	return *Bx;
};
MatrixXd Bezier::get_By() {
	return *By;
};

double Bezier::cubic_bezier(double t, int x0, int x1, int x2, int x3) {
	double s = 1 - t;
	return  s * s * s * x0 + 3 * s * s * t * x1 + 3 * s * t * t * x2 + t * t * t * x3;
}
MatrixXi Bezier::cubic_interpolation(double t) {
	int index = floor(t / (double)plot_resolution);
	double t_rescaled = t - index * plot_resolution;
	MatrixXi interpo(1, dim);
	if (index != Nb_bezigons - 1) {
		interpo(0, 0) = int(cubic_bezier(t_rescaled, get_ptx(index, 0), get_ptx(index, 1), get_ptx(index, 2), get_ptx(index + 1, 0)));
		interpo(0, 1) = int(cubic_bezier(t_rescaled, get_pty(index, 0), get_pty(index, 1), get_pty(index, 2), get_pty(index + 1, 0)));
	}
	else {
		interpo(0, 0) = int(cubic_bezier(t_rescaled, get_ptx(index, 0), get_ptx(index, 1), get_ptx(index, 2), get_ptx(0, 0)));
		interpo(0, 1) = int(cubic_bezier(t_rescaled, get_pty(index, 0), get_pty(index, 1), get_pty(index, 2), get_pty(0, 0)));
	}
	return interpo;
}

MatrixXi Bezier::get_sample_points() {
	double dt = 1. / plot_resolution;
	MatrixXi curve(Nb_bezigons * plot_resolution, dim);
	for (size_t ii = 0; ii < Nb_bezigons; ii++) {
		for (size_t jj = 0; jj < plot_resolution; jj++) {
			curve.row(ii * plot_resolution + jj) = cubic_interpolation(ii * plot_resolution + jj * dt);
		}
	}
	return curve;
}

void Bezier::plot_curve(Image<cv::Vec3b> I) {
	MatrixXi curve = get_sample_points();
	for (int i = 0; i < curve.rows(); i++) {
		Point m1 = Point(curve.row(i)[0], curve.row(i)[1]);
		circle(I, m1, 1, cv::Scalar(0, 255, 0), 2);
		imshow("Plot bezier", I);
		waitKey(1);
	}
}



//
// Color entity:
//

Color::Color(int _dim) {
	dim = _dim;
	C = new MatrixXd(_dim, 3);
	C->setZero();
};
Color::Color(const MatrixXd& _C) {
	dim = _C.rows();
	C = new MatrixXd(dim, 3);
	*C = _C;

};
int Color::getColorImage(int x, int y) {
	return 0;
};
void Color::setColor(int index, int RGB, int color) {
	C->row(index)[RGB] = color;
};
void Color::print_Matrix() {
	std::cout << *C << std::endl;
};

//
// VectorizationData entity:
//

VectorizationData::VectorizationData(Bezier* _B, Color* _C, Image<Vec3b> _I) {
	B = _B;
	C = _C;
	I = _I;
}