#pragma once

#ifndef PROPAGATION_H_INCLUDED
#define PROPAGATION_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Initialisation.h"
#include "Energy.h"

class Propagation {
public:
	void propagation();
};

#endif