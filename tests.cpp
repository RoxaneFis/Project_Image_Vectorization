#include "Tests.h"

using namespace cv;


void test_compute_angles(VectorizationData vd){
    	std::cout<<"Nb bezigons "<<vd.B->Nb_bezigons<<std::endl; 
        for (int j=0; j<vd.B->nb_points(); j++){
			std::array<std::vector<double>,2> tangents_j= vd.B->get_tangents(j);
			std::vector<double> a_j = tangents_j[0];
			std::vector<double> b_j = tangents_j[1];
			double scalar_multiplication = inner_product(begin(a_j),end(a_j),begin(b_j),0.0);
			double angle = acos(scalar_multiplication/(norm(a_j)*norm(b_j)));
            if (isnan(angle)){
			    std::cout<<"The angle of point "<<j<<" is not defined : it may come from duplicates "<<angle*380/(2*M_PI)<<std::endl; 
            }
            else{
			    std::cout<<"The angle of point "<<j<<" is (in degres) : "<<angle*380/(2*M_PI)<<std::endl; 

            }
		}
        std::cout<<std::endl; 

};



void test_compute_energy_angles(VectorizationData vd){
        double energy = 0.0;
		for (int j=0; j<vd.B->Nb_bezigons; j++){
			std::array<std::vector<double>,2> tangents_j= vd.B->get_tangents(j);
			std::vector<double> a_j = tangents_j[0];
			std::vector<double> b_j = tangents_j[1];
			double scalar_multiplication = inner_product(begin(a_j),end(a_j),begin(b_j),0.0);
			double angle = acos(scalar_multiplication/(norm(a_j)*norm(b_j)));
            if(angle !=0 && !isnan(angle)){
                energy =+ 1/(angle);

            }
		}
		std::cout<<"The Angles Energy is "<<energy<<std::endl; 

};