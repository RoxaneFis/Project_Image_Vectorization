#include "Propagation.h"
#include <ctime>

Propagation::Propagation(VectorizationData _vd) {
	energy = new Energy();
	vd = new VectorizationData(_vd.B,_vd.I);
};



void Propagation::propagate(int nb_iterations, double alpha, double eps, string name) {
	cout << ">>>Enter Propragation" << std::endl;
	clock_t begin = clock();

	//WRITE
	fstream out;
    out.open(name, fstream::out);
	out << "Hyperparameters : \n"<<"Epsilon : "<<eps<<"\nAlpha : "<<alpha <<"\nTaille Image "<<vd->I.width() <<"x" <<vd->I.height();
	out<<"\nLambda_data :"<<energy->lambda_data<<"\nLambda_handles: "<<energy->lambda_handles<<"\nLamda_angles :"<<energy->lambda_angles<<"\nLamda_legnth :"<<energy->lambda_length<<endl;
	out<<"\nEnergies intialization:";
	out<<"\nE_data :"<<energy->energy_data(*vd)<<"\nE_handes :"<<energy->energy_bezier_handles(vd->B)<<"\nE_angles :"<<energy->energy_angles(vd->B)<<"\nE_length :"<<energy->energy_curve_length(vd->B)<<endl;;


	//NB OF PROPAGATIONS
	for (int iter=0; iter<nb_iterations; iter++){
		out <<"\nPROPAGATION : "<<iter<<endl;;
		//out<<"\nAlpha_updated :"<<alpha<<endl;;

		//ITERATIONS OVER ALL BEZIERS
		for (int jj=0; jj<vd->B.Bx.rows(); jj++){
			
			//PARAMETERS
			array<double,10> vals_inp = vd->B.input_propagation(jj); 
			array<double,10> vals_copy_plus =vals_inp ;
			array<double,10> vals_copy_moins =vals_inp ;
			array<double,10> vals_out;

			double engy_prece=energy->energy_partial(*vd,jj);
			out <<"\nBezier Nb: "<<jj<<"\nPartial_Energy : "<<engy_prece<<endl;

			for(int var_index=0; var_index<10; var_index++){
				double grad=0.0;
				vals_copy_plus[var_index]=vals_inp[var_index]+eps;
				vals_copy_moins[var_index]=vals_inp[var_index]-eps;
				double engy_plus = energy->energy_to_minimize(*vd,jj,vals_copy_plus);
				double engy_moins = energy->energy_to_minimize(*vd,jj,vals_copy_moins);
				grad = (engy_plus-engy_moins)/(2*eps);
				out << "Grad: "<<grad<<endl;
				int width = vd->I.width();
				int height = vd->I.height();
				// while(norm(alpha*grad)>min(width,height)/15)	{
				// 	grad=grad/10;
				// }	
				cout << "energy_plus: "<<engy_plus<<endl;	
				cout << "energy_moins: "<<engy_moins<<endl;	
				cout << endl;	
				
				// cout << endl;
				vals_copy_plus[var_index]=vals_inp[var_index]-alpha*grad;
				vals_copy_moins[var_index]=vals_inp[var_index]-alpha*grad;
				vals_out[var_index]=vals_inp[var_index]-alpha*grad;
			};
			vd->B.update(vals_out,jj);
		}
		if(iter%3==0){

			vd->B.plot_curve(vd->I," Iter :"+to_string(iter)+" "+name);
			rms(*vd, to_string(iter)+" RMS "+name);
		}
	}
	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	out<<"Propagation time : "<<elapsed_secs/60.0<<" minutes"<<endl;
	out.close();
}





	// //PARAMETERS
	// 		array<double,10> vals_inp = vd->B.input_propagation(jj); 
	// 		array<double,10> vals_copy_plus =vals_inp ;
	// 		array<double,10> vals_copy_moins =vals_inp ;
	// 		array<double,10> vals_out;

	// 		double engy_prece=energy->energy_partial(*vd,jj);
	// 		double total_energy = energy->energy_data(*(vd));
	// 		out <<"\nBezier Nb: "<<jj<<"\nTotal_Energy : "<<total_energy<<"\nPatial_Energy : "<<engy_prece<<endl;

	// 		for(int var_index=0; var_index<10; var_index++){
	// 			double grad=0.0;
	// 			vals_copy_plus[var_index]=vals_inp[var_index]+eps;
	// 			vals_copy_moins[var_index]=vals_inp[var_index]-eps;
	// 			double engy_plus = energy->energy_to_minimize(*vd,jj,vals_copy_plus);
	// 			double engy_moins = energy->energy_to_minimize(*vd,jj,vals_copy_moins);
	// 			grad = ((engy_plus-engy_moins)/(2*eps));		
	// 			out << "Grad: "<<grad<<endl;
	// 			cout << "energy_plus: "<<engy_plus<<endl;	
	// 			cout << "energy_moins: "<<engy_moins<<endl;	
	// 			// cout << endl;
	// 			vals_copy_plus[var_index]=vals_inp[var_index]-alpha*grad;
	// 			vals_copy_moins[var_index]=vals_inp[var_index]-alpha*grad;
	// 			vals_out[var_index]=vals_inp[var_index]-alpha*grad;