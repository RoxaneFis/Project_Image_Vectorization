#include "Propagation.h"

Propagation::Propagation(VectorizationData _vd) {
	energy = new Energy();
	vd = &_vd;
};

void Propagation::propagate(int nb_iterations) {
	std::cout << ">>>Enter Propragation" << std::endl;
		for (int j=0; j<1; j++){

		//By calling energy_unknown, vd->B is updated
		auto energy_unknown = [this,j](matrix<double,10,1>x) 
		{return energy->energy_to_minimize(*(this->vd),j,x); };

		// auto result =find_min_global(energy_unknown,{0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1}, {2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1},max_function_calls(100),0);
	    // auto rosen = [](const matrix<double,0,1>& x) { return -1*( 100*std::pow(x(1) - x(0)*x(0),2.0) + std::pow(1 - x(0),2)); };
        // auto result = find_max_global(rosen, {0.1, 0.1}, {2, 2}, max_function_calls(100), 0);
        // matrix<double,0,1> true_x = {1,1};


		
		//cout<<"test"<<result_test.x<<endl;

		// auto result =dlib::find_min_global(energy_unknown, {-0.1, -0.1, -0.1, -0.1,-0.1,  -0.1,-0.1,-0.1,-0.1,-0.1}, 
		// {2, 2, 2,2,2 ,2,2,2,2,2}, dlib::max_function_calls(100));
		//dlib::find_min_global(energy_unknown,)
		// std::cout << result.x << std::endl;

	}
}