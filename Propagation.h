#pragma once

#ifndef PROPAGATION_H_INCLUDED
#define PROPAGATION_H_INCLUDED

#include <iostream>
#include <ostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Entities.h"
#include "Energy.h"

class Propagation {
public:
	VectorizationData* vd;
	Energy *energy;
	Propagation(VectorizationData _vd);
	void propagate(int nb_iterations, double alpha, double eps, string name);
};

#endif