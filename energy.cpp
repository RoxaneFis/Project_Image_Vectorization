#include "Energy.h"

using namespace cv;

Energy::Energy(){};

double Energy::energy_angles(Bezier B){
	//Compute the prior Energy for angle variations
		std::cout<<"Nb bezigons "<<B.Nb_bezigons<<std::endl; 
		for (int j=1; j<B.Nb_bezigons-1; j++){
			std::array<std::vector<double>,2> tangents_j= B.get_tangents(j);
			std::vector<double> a_j = tangents_j[0];
			std::vector<double> b_j = tangents_j[1];
			double scalar_multiplication = inner_product(begin(a_j),end(a_j),begin(b_j),0.0);
			double angle = acos(scalar_multiplication/(norm(a_j)*norm(b_j)));
			std::cout<<"L'angle du point "<<j<<" vaut (en degres) : "<<angle*380/(2*M_PI)<<std::endl; 

		}
		return 0;

	}

