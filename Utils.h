#pragma once

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <math.h>
#define EQN_EPS 1e-9

cv::Point2f barycenter(double t, cv::Point2f A, cv::Point2f B);
double distance(cv::Point2f A, cv::Point2f B);
double angle(cv::Point2f A, cv::Point2f B, cv::Point2f C);
double det(cv::Point2f A, cv::Point2f B);

static int isZero(double x);
int solveLinear(double c1, double c0, double& s0);
int solveQuadric(double c2, double c1, double c0, double& s0, double& s1);
int solveCubic(double c3, double c2, double c1, double c0, double& s0, double& s1, double& s2);
std::vector<double> get_roots(double c3, double c2, double c1, double c0);

#endif