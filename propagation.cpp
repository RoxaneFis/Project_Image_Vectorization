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
	std::cout << ">>>Enter Propragation" << std::endl;
	for (int jj=0; jj<vd->B->Nb_bezigons; jj++){
		//Call to energy_to_minimize : B is updated
		auto energy_unknown = [this,jj](const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data) 
		{ 	this->vd->B->update(vals_inp,jj);
			return energy->energy_tot(*vd,jj);};

		// arma::vec* grad_out;
		// void* opt_data;
    	
		// vd->B->print_Bx();
		// arma::vec x = vd->B->input_propagation(jj); 
		// arma::cout << "x_in" << x << arma::endl;
		// arma::cout << "erngy" << energy->energy_tot(*vd,jj) << arma::endl;
		// arma::cout << "erngy_U" << energy_unknown(x,grad_out,opt_data) << arma::endl;

    	// //bool success = optim::de(x,energy_unknown,nullptr);
		// bool success = optim::gd(x,energy_unknown,nullptr);
		// arma::cout << "\nde: solution to Ackley test:\n" << x << arma::endl;
	}

}




