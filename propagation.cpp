#include "Propagation.h"

Propagation::Propagation(VectorizationData _vd) {
	energy = new Energy();
	vd = &_vd;
};



// double cost_function(const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data)
// {
// 	Energy* energy = new Energy();
// 	return energy->energy_to_minimize()

// }

void Propagation::propagate(int nb_iterations) {
	double eps = 0.1;
	double energy_prece = 0.0;
	cout << ">>>Enter Propragation" << std::endl;
	for (int jj=0; jj<vd->B->Nb_bezigons; jj++){
		array<double,10> vals_inp = vd->B->input_propagation(jj); 
		array<double,10> vals_copy =vals_inp ;
		array<double,10> vals_out; 
		double engy = 0.0;	
		double engy_min=-1;	
		double trans_ind;	
		for(int var_index=0; var_index<10; var_index++){
			trans_ind=-5;
			for(int  trans= -5; trans<6; trans++ ){	
				//just change one value by eps*trans
				vals_copy[var_index]=vals_inp[var_index]+eps*trans;
				engy =energy->energy_to_minimize(*vd,jj,vals_copy);
				if(engy<=engy_min){
					engy_min = engy;
					trans_ind = trans;
				}
			}
			vals_out[var_index]=vals_inp[var_index]+eps*trans_ind;
		}
		vd->B->update(vals_out,jj);



	}

}




