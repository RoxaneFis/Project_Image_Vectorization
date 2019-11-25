#include "Energy.h"

using namespace cv;

Energy::Energy(){};

double Energy::energy_angles(Bezier B){
	//Compute the prior Energy for angle variations
	double energy = 0.0;
		for (int j=0; j<B.nb_points(); j++){
			std::array<std::vector<double>,2> tangents_j= B.get_tangents(j);
			std::vector<double> a_j = tangents_j[0];
			std::vector<double> b_j = tangents_j[1];
			double scalar_multiplication = inner_product(begin(a_j),end(a_j),begin(b_j),0.0);
			double angle = acos(scalar_multiplication/(norm(a_j)*norm(b_j)));
			if(angle !=0 && !isnan(angle)){
				energy =+ 1/(angle);
			}

		}
		return energy;

	}

