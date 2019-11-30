#include "Energy.h"

using namespace cv;

Energy::Energy(){};


double Energy::energy_angles(Bezier B, int point){
	//Compute the prior Energy for angle variations
		std::array<std::vector<double>,2> tangents_j= B.get_tangents(point);
		std::vector<double> a_j = tangents_j[0];
		std::vector<double> b_j = tangents_j[1];
		double scalar_multiplication = inner_product(begin(a_j),end(a_j),begin(b_j),0.0);
		double angle = acos(scalar_multiplication/(norm(a_j)*norm(b_j)));
		//In case we are dealing with the same point			
			if(angle !=0 && !isnan(angle)){
				return 1/(angle);
			}
			else{ return 0.0;}

		}

double Energy::energy_angles(Bezier B){
	double energy = 0.0;
		for (int j=0; j<B.nb_points(); j++){
			energy = energy+ energy_angles(B,j);

		}
		return energy;
	}


double Energy::energy_bezier_handles(Bezier B, int point){
	std::array<std::vector<double>,2> tangents_j= B.get_tangents(point);
	std::vector<double> a_j = tangents_j[0];
	std::vector<double> b_j = tangents_j[1];

	//In case we are dealing with the same point
	if(( norm(a_j)>0 && norm(b_j)>0)){
		return 1/norm(a_j) + 1/norm(b_j);
	}
	else{return 0.0;};

}

double Energy::energy_bezier_handles(Bezier B){
	double energy = 0.0;
		for (int j=0; j<B.nb_points(); j++){
			energy = energy+energy_bezier_handles(B,j);
		}
		return energy;
};

double Energy::energy_data(VectorizationData vd){
	double lo = 100000.0*100000.0;
	double energy = 0.0;
	Image<float> rasterized = get_rasterized(vd);
	for (size_t ii = 0; ii < vd.I.rows; ii++) {
		for (size_t jj = 0; jj < vd.I.cols; jj++) {
			Vec3b ras = rasterized.at<Vec3b>(ii, jj);
			Vec3b im = vd.I.at<Vec3b>(ii, jj);
			energy += pow(norm((ras)-(im)),2);
		}
	};
	return energy/lo;
};
	


double Energy::energy_tot(VectorizationData vd, int j){

	double energy_prior= lambda_angles*energy_angles(*(vd.B),j)+lambda_handles*energy_bezier_handles(*(vd.B),j);
	double energy =energy_data(vd);
	return energy+energy_prior;
	
};

double Energy::energy_to_minimize(VectorizationData vd, int j, dlib::matrix<double,10,1>x){
	vd.B->update(x,j);
	return energy_tot(vd,j);
}
	
