#include "Propagation.h"

Propagation::Propagation(VectorizationData _vd) {
	energy = new Energy();
	vd = &_vd;
};

void Propagation::propagate(int nb_iterations) {
	std::cout << ">>>Enter Propragation" << std::endl;
};
