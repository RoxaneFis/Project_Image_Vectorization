#pragma once

#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

#include <iostream>
#include <csignal>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOFF.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Entities.h"

struct VectorPoints {
	std::vector<cv::Point> vector_points;
	cv::Mat image;
};

const std::string WINDOW_NAME = "Init";
VectorizationData initialisation(const cv::Mat& I);
void onMouse(int event, int x, int y, int flags, void* userdata);

#endif