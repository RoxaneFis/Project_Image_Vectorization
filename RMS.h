#pragma once

#ifndef RMS_H_INCLUDED
#define RMS_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Entities.h"
#include "image.h"

void rms();
int phi(double t);
int psi(double t);
int phi_s_k(double t, int s, int k);
int psi_s_k(double t, int s, int k);
Eigen::Matrix2i haar(int s, int kx, int ky, double x, double y);
bool is_interior(cv::Point, Bezier B);
void show_interior(VectorizationData vd);

#endif