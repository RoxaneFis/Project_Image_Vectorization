#pragma once

#ifndef PROPAGATION_H_INCLUDED
#define PROPAGATION_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <dlib/global_optimization.h>

#include "Entities.h"
#include "Energy.h"

using namespace dlib;

class Propagation {
public:
	VectorizationData* vd;
	Energy *energy;
	Propagation(VectorizationData _vd);
	void propagate(int nb_iterations);
};

#endif