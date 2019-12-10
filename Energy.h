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
	double energy_angles_ctrl_pt(Bezigon B, int point) ;
	double energy_angles(Bezigon B, int point); 
	double energy_angles(Bezigon B);

	double energy_bezier_handles_ctrl_pt(Bezigon B, int point);
	double energy_bezier_handles(Bezigon B, int point);
	double energy_bezier_handles(Bezigon B);

	double energy_data(VectorizationData vd);
	double energy_partial(VectorizationData vd, int j );
	double energy_to_minimize(VectorizationData vd, int j, array<double, 10> vals_inp);

	const double lambda_angles = (1.0/20.0)*1000;
	const double lambda_handles = (1.0/2.0)*1000;
	const double lambda_data = (1.0/2500.0)*100000;

};



#endif