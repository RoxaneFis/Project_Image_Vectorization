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
private:
	const double lambda_angles = (1.0/40.0)*1000;
	const double lambda_handles = (1.0/2.0)*1000;
public:
	Energy();
	double energy_angles(Bezigon B, int point) ;
	double energy_angles(Bezigon B);
	double energy_bezier_handles(Bezigon B, int point);
	double energy_bezier_handles(Bezigon B);

	double energy_data(VectorizationData vd);
	double energy_tot(VectorizationData vd, int j );
	double energy_to_minimize(VectorizationData vd, int j, array<double, 10> vals_inp);


};



#endif