#pragma once
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
#include "Image.h"

struct VectorPoints {
	std::vector<cv::Point>* vector_points;
	Image<Vec3b> image;
	Image<Vec3b> image_copy;
};

const std::string WINDOW_NAME = "Init";
VectorizationData initialisation(Image<Vec3b> I);
void onMouse(int event, int x, int y, int flags, void* p);

#endif