#include "Propagation.h"

Propagation::Propagation(VectorizationData _vd) {
	energy = new Energy();
	vd = new VectorizationData(_vd.B,_vd.I);
};


#include <cstdio>
#include <string>
#include <cassert>

template< typename... Args >
std::string string_sprintf( const char* format, Args... args ) {
  int length = std::snprintf( nullptr, 0, format, args... );
  assert( length >= 0 );

  char* buf = new char[length + 1];
  std::snprintf( buf, length + 1, format, args... );

  std::string str( buf );
  delete[] buf;
  return str;
}



void Propagation::propagate(int nb_iterations, double alpha) {
	double eps = 0.001;
	cout << ">>>Enter Propragation" << std::endl;
	for (int jj=0; jj<vd->B.Bx.rows(); jj++){
		array<double,10> vals_inp = vd->B.input_propagation(jj); 
		array<double,10> vals_copy =vals_inp ;
		array<double,10> vals_out; 
	    double engy_prece=energy->energy_tot(*vd,jj);
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
			}
            vals_copy[var_index]=vals_inp[var_index]-alpha*grad;
		};
		
		vd->B.update(vals_copy,jj);
		vd->B.plot_curve(vd->I,to_string(jj));

	}
}




