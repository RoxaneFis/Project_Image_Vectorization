#pragma once

#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Bezier
{
private:
	int Nb_bezigons;
	Eigen::MatrixXd* Bx;
	Eigen::MatrixXd* By;

public:
	Bezier(int N);
	Bezier(const Eigen::MatrixXd& B_x, const Eigen::MatrixXd& B_y);
	float arclength();
	Eigen::MatrixXd intersection();
	void set_point_x(int i, int j, int coord_x);
	void set_point_y(int i, int j, int coord_y);
	void print_Bx();
	void print_By();
};

class Color
{
private:
	Eigen::MatrixXd* C; //Co a C5
	int dim;

public:
	Color(int _dim);
	Color(const Eigen::MatrixXd& _C);
	int getColorImage(int x, int y);
	void setColor(int index, int RGB, int color);
	void print_Matrix();
};


struct VectorizationData
{
	Bezier* B;
	Color* C;
	cv::Mat I;
	VectorizationData(Bezier* _B, Color* _C, cv::Mat _I);
};

#endif