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

class Energy {
public:
	void energy();
};

#endif