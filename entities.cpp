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
Bezier::Bezier(const std::vector<cv::Point>& vector_points){
	//Initialise Bezier matrices from a Vector of points. If the number of points
	//differs from 3*n, we add the last one several times.
	int jj=0;
	int nb_points = vector_points.size();
	Nb_bezigons = ceil((double(nb_points)/3.0));
	int remaining_points=Nb_bezigons*3-nb_points;
	By = new MatrixXd(Nb_bezigons, 3);
	Bx = new MatrixXd(Nb_bezigons, 3);
	for(int ii=0; ii<nb_points;ii++){
			Bx->row(int(ii/3))[jj]=double(vector_points[ii].x);
			By->row(int(ii/3))[jj]=double(vector_points[ii].y);
			jj=int((jj+1)%3);
			
		}
	//Add the last point several times
	for (int ii=0;ii<remaining_points;ii++){
			Bx->row(Nb_bezigons-1)[jj]=double(vector_points[nb_points-1].x);
			By->row(Nb_bezigons-1)[jj]=double(vector_points[nb_points-1].y);
			jj=int((jj+1)%3);}
}
std::array<std::vector<double>,2> Bezier::get_tangents(int j){
	//Returns left et right tangents of a point
	//FIXME : doesnt take first and last true points into account
	std::array<std::vector<double>,2> tangents;
	vector<double> left_tangent(2) ;
	vector<double> right_tangent(2) ;
	if (j==0){
		std::cout<<"Error :Point at the beginning of the curve"<<std::endl;
		return tangents;
	}
	if (j>=Nb_bezigons){
		std::cout<<"The index is too high. The point doesn't exist"<<std::endl;
		return tangents;
	}
	else
	{
		left_tangent={get_ptx(j,0)-get_ptx(j-1,2),get_pty(j,0)-get_pty(j-1,2)};
		right_tangent={get_ptx(j,2)-get_ptx(j,0),get_pty(j,2)-get_pty(j,0)};
		return {left_tangent, right_tangent};
	}
}


float Bezier::arclength() {
	//Returns the arclegth of the Bezigon
	return 0.0;
};

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
	return Bx->row(i)[j] ;
};
double Bezier::get_pty(int i, int j) {
	return By->row(i)[j] ;
};
void Bezier::print_Bx() {
	std::cout <<"Print Bx "<< *Bx << std::endl;
};
void Bezier::print_By() {
	std::cout <<"Print By"<< *By << std::endl;
};

double Bezier::cubic_bezier(double t,int x0,int x1,int x2,int x3){
       double s = 1-t;
       return  int(s*s*s*x0 + 3*s*s*t*x1 + 3*s*t*t*x2 + t*t*t*x3);
}
MatrixXi Bezier::cubic_interpolation(double t){
       int index=std::floor(t*Nb_bezigons);
	   double t_rescaled = (Nb_bezigons)*t-index;
       MatrixXi interpo(1, dim);
       if(index != Nb_bezigons-1){
           interpo(0,0)= int(cubic_bezier(t_rescaled,get_ptx(index, 0),get_ptx(index, 1),get_ptx(index, 2),get_ptx(index+1,0)));
           interpo(0,1)= int(cubic_bezier(t_rescaled,get_pty(index, 0),get_pty(index, 1),get_pty(index, 2),get_pty(index+1,0)));
       }
		else {
	        interpo(0,0)= int(cubic_bezier(t_rescaled,get_ptx(index, 0),get_ptx(index, 1),get_ptx(index, 2),get_ptx(index, 2)));
	        interpo(0,1)= int(cubic_bezier(t_rescaled,get_pty(index, 0),get_pty(index, 1),get_pty(index, 2),get_pty(index, 2)));
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