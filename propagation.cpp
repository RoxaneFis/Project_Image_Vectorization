#include "Propagation.h"

Propagation::Propagation(VectorizationData _vd) {
	energy = Energy();
	vd = &_vd;
};

void Propagation::propagate() {
	double energyAngles = energy.energy_angles(*(vd->B));
}