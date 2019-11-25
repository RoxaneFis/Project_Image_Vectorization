#pragma once

#ifndef ENERGY_H_INCLUDED
#define ENERGY_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "RMS.h"
#include "Entities.h"

class Energy {
public:
	Energy();
	double energy_angles(Bezier B, int point);
	double energy_angles(Bezier B);
	double energy_bezier_handles(Bezier B, int point);
	double energy_bezier_handles(Bezier B);

};



#endif