#pragma once

#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOFF.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Entities.h"


struct Vector_Points{
    std::vector<cv::Point> vector_points;
    cv::Mat image;
};

void initialisation();
void onMouse(int event, int x, int y, int foo, void* p);
void initialisation_on_mouse(cv::Mat Image);

#endif