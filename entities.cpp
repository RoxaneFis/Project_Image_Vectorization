#include "Entities.h"

using namespace cv;
using namespace std;
using namespace Eigen;

//
// Bezier entity:
//

Bezier::Bezier(int N) {
	Nb_bezigons = N;
	By = new Eigen::MatrixXi(N, 3);
	Bx = new Eigen::MatrixXi(N, 3);
	By->setZero();
	Bx->setZero();
};

Bezier::Bezier(const MatrixXi& B_x, const MatrixXi& B_y) {
	Nb_bezigons = B_x.rows();
	By = new MatrixXi(Nb_bezigons, 3);
	Bx = new MatrixXi(Nb_bezigons, 3);
	*Bx = B_x;
	*By = B_y;
};
Bezier::Bezier(const std::vector<cv::Point>& vector_points){
	int index =0;
	int nb_points = vector_points.size();
	Nb_bezigons = int(nb_points/3);
	By = new MatrixXi(Nb_bezigons, 3);
	Bx = new MatrixXi(Nb_bezigons, 3);
	for(int ii=0; ii<Nb_bezigons;ii++){
		for (int jj=0;jj<3;jj++){
			Bx->row(ii)[jj]=vector_points[index].x;
			By->row(ii)[jj]=vector_points[index].y;
			index++;
		}
	}
}

float Bezier::arclength() {
	//Returns the arclegth of the Bezigon
	return 0.0;
};

MatrixXi Bezier::intersection() {
	//Returns points that intersect // Maybe directly in Energy?
	MatrixXi inter;
	return inter;
};
void Bezier::set_point_x(int i, int j, int coord_x) {
	Bx->row(i)[j] = coord_x;
};
void Bezier::set_point_y(int i, int j, int coord_y) {
	By->row(i)[j] = coord_y;
};
int Bezier::get_ptx(int i, int j) {
	return Bx->row(i)[j] ;
};
int Bezier::get_pty(int i, int j) {
	return By->row(i)[j] ;
};
void Bezier::print_Bx() {
	std::cout <<"Print Bx "<< *Bx << std::endl;
};
void Bezier::print_By() {
	std::cout <<"Print By"<< *By << std::endl;
};

int Bezier::cubic_bezier(double t,int x0,int x1,int x2,int x3){
       double s = 1-t;
       return  int(s*s*s*x0 + 3*s*s*t*x1 + 3*s*t*t*x2 + t*t*t*x3);
}
MatrixXi Bezier::cubic_interpolation(double t){
       int index=std::floor(t*Nb_bezigons);
	   double t_rescaled = (Nb_bezigons)*t-index;
       MatrixXi interpo(1, dim);
       if(index != Nb_bezigons-1){
           interpo(0,0)= cubic_bezier(t_rescaled,get_ptx(index, 0),get_ptx(index, 1),get_ptx(index, 2),get_ptx(index+1,0));
           interpo(0,1)= cubic_bezier(t_rescaled,get_pty(index, 0),get_pty(index, 1),get_pty(index, 2),get_pty(index+1,0));
       }
		else {
	        interpo(0,0)= cubic_bezier(t_rescaled,get_ptx(index, 0),get_ptx(index, 1),get_ptx(index, 2),get_ptx(index, 2));
	        interpo(0,1)= cubic_bezier(t_rescaled,get_pty(index, 0),get_pty(index, 1),get_pty(index, 2),get_pty(index, 2));
	    }
       return interpo;
   }
MatrixXi Bezier::plot_curve(Image<cv::Vec3b> I ){
   double dt = 1. / (plot_resolution - 1);
   MatrixXi curve(plot_resolution,dim);
   for (int i=0;i<plot_resolution-1;i++){
     curve.row(i)=cubic_interpolation(i*dt); 
	 Point m1 = Point( curve.row(i)[0],curve.row(i)[1]);
	 circle (I,m1,2, cv::Scalar(0,255,0),2);
	 imshow("Plot bezier", I);
	 waitKey(1);
   }
   return curve;
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

VectorizationData::VectorizationData(Bezier* _B, Color* _C, cv::Mat _I) {
	B = _B;
	C = _C;
	I = _I;
}