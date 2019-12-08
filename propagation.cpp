#include "Propagation.h"

Propagation::Propagation(VectorizationData _vd) {
	energy = new Energy();
	vd = new VectorizationData(_vd.B,_vd.I);
};



void Propagation::propagate(int nb_iterations, double alpha, int numero_test) {
	cout << ">>>Enter Propragation" << std::endl;
	double eps = 0.001;
	alpha = 0.0001;
	
	//WRITE
	string filename = "test_Energy_data_" + to_string(numero_test);
	fstream out;
    out.open(filename, fstream::out);
	out << "Hyperparameters : \n"<<"Epsilon : "<<eps<<"\nAlpha : "<<alpha<<"\nLambda_data: "<<energy->lambda_data<<endl;

	
	//ITERATIONS OVER ALL BEZIERS
	for (int jj=0; jj<vd->B.Bx.rows(); jj++){
		array<double,10> vals_inp = vd->B.input_propagation(jj); 
		array<double,10> vals_copy =vals_inp ;
		array<double,10> vals_out;

	    double engy_prece=energy->energy_partial(*vd,jj);
		double total_energy = energy->energy_data(*(vd));

		out <<"\nBezier Nb: "<<jj<<"\nTotal_Energy : "<<total_energy<<"\nPatial_Energy : "<<engy_prece<<endl;

        //cout << jj<<" E_bezier =  "<<total_energy << endl;
		double engy_to_min = 0.0;	

		for(int var_index=0; var_index<10; var_index++){
        	double grad=0.0;	
			for(int  i=-1; i<=1; i++){
				if(i!=0){
					vals_copy[var_index]=vals_inp[var_index]+eps*i;
					engy_to_min = energy->energy_to_minimize(*vd,jj,vals_copy);
					if(engy_to_min<engy_prece){
						grad = double((engy_to_min-engy_prece)/(i*eps));
						engy_prece = engy_to_min;
						}
				}
			vals_copy[var_index]=vals_inp[var_index];
			}
			out << "Grad: "<<grad<<endl;

			// cout << "Grad "<< grad<<endl;
			// cout << "index "<< vals_copy[var_index]<<endl;
			// cout<<endl;
            vals_out[var_index]=vals_inp[var_index]-alpha*grad;
		};
		vd->B.update(vals_out,jj);
		vd->B.plot_curve(vd->I,to_string(jj));
	}
	out.close();
}



