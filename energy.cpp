#include "Energy.h"

using namespace cv;
using namespace std;

//Energy::Energy() {};
//
//
//double Energy::energy_angles(Bezier B, int point) {
//	//Compute the prior Energy for angle variations
//	array<vector<double>, 2> tangents_j = B.get_tangents(point);
//	vector<double> a_j = tangents_j[0];
//	vector<double> b_j = tangents_j[1];
//	double scalar_multiplication = inner_product(begin(a_j), end(a_j), begin(b_j), 0.0);
//	double angle = acos(scalar_multiplication / (norm(a_j) * norm(b_j)));
//	//In case we are dealing with the same point			
//	if (angle != 0 && !isnan(angle)) {
//		return 1 / (angle);
//	}
//	else { return 0.0; }
//
//}
//
//double Energy::energy_angles(Bezier B) {
//	double energy = 0.0;
//	for (int j = 0; j < B.nb_points(); j++) {
//		energy = energy + energy_angles(B, j);
//
//	}
//	return energy;
//}
//
//double Energy::energy_bezier_handles(Bezier B, int point) {
//	array<vector<double>, 2> tangents_j = B.get_tangents(point);
//	vector<double> a_j = tangents_j[0];
//	vector<double> b_j = tangents_j[1];
//
//	//In case we are dealing with the same point
//	if ((norm(a_j) > 0 && norm(b_j) > 0)) {
//		return 1 / norm(a_j) + 1 / norm(b_j);
//	}
//	else { return 0.0; };
//
//}
//
//double Energy::energy_bezier_handles(Bezier B) {
//	double energy = 0.0;
//	for (int j = 0; j < B.nb_points(); j++) {
//		energy = energy + energy_bezier_handles(B, j);
//	}
//	return energy;
//};
//
//double Energy::energy_data(VectorizationData vd) {
//	double lo = vd.B->lo;
//	double energy = 0.0;
//	Image<Vec3b> rasterized = get_rasterized(vd);
//	for (size_t xx = 0; xx < vd.I.width(); xx++) {
//		for (size_t yy = 0; yy < vd.I.height(); yy++) {
//			Vec3b ras = rasterized(xx, yy);
//			Vec3b im = vd.I(xx, yy);
//			energy += pow(norm((ras)-(im)), 2);
//		}
//	};
//	return energy / (lo*10000000);
//};
//
//
//
//double Energy::energy_tot(const VectorizationData vd, int j) {
//	double energy_prior = lambda_angles * energy_angles(*(vd.B), j) + lambda_handles * energy_bezier_handles(*(vd.B), j);
//	double energy = energy_data(vd);
//	// cout << "E_bezier_handles"<<energy_bezier_handles(*(vd.B), j)<<endl;
//	// cout << "E_angles"<<energy_angles(*(vd.B), j)<<endl;
//	// cout << "E_data"<<energy<<endl;
//	return energy + energy_prior;
//
//};
//
//
//double Energy::energy_to_minimize(const VectorizationData vd, int j, const array<double, 10>& vals_inp){
//	Eigen::MatrixXd Bx_prime = *(vd.B->Bx);
//	Eigen::MatrixXd By_prime = *(vd.B->Bx);
//	Bezier * B_prime = new Bezier(Bx_prime,By_prime);
//	VectorizationData vd_prime(B_prime,vd.C,vd.I);
//	B_prime->update(vals_inp,j);
//	return energy_tot(vd_prime,j);
//}

