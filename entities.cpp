#include "Entities.h"

using namespace cv;
using namespace std;
using namespace Eigen;

//
// Initializing Bezier entity:
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

float Bezier::arclength() {
	//Returns the arclegth of the Bezigon
	return 0.0;
};

MatrixXd Bezier::intersection() {
	//Returns points that intersect // Maybe directly in Energy?
	MatrixXd inter;
	return inter;
};
void Bezier::set_point_x(int i, int j, int coord_x) {
	Bx->row(i)[j] = coord_x;
};
void Bezier::set_point_y(int i, int j, int coord_y) {
	By->row(i)[j] = coord_y;
};
void Bezier::print_Bx() {
	std::cout << *Bx << std::endl;
};
void Bezier::print_By() {
	std::cout << *By << std::endl;
};


//
// Initializing Color entity:
//

Color::Color(int _dim) {
	dim = _dim;
	C = new MatrixXd(_dim, 3);
	C->setZero();
};

Color::Color(const MatrixXd& C_) {
	dim = C_.rows();
	C = new MatrixXd(dim, 3);
	*C = C_;

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