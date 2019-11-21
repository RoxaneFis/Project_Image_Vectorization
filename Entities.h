#pragma once

#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Image.h"

class Bezier
{
private:
	int Nb_bezigons;
	const int plot_resolution = 500;
	const int dim = 2;
	Eigen::MatrixXi* Bx;
	Eigen::MatrixXi* By;

public:
	Bezier(int N);
	Bezier(const Eigen::MatrixXi& B_x, const Eigen::MatrixXi& B_y);
	Bezier(const std::vector<cv::Point>& vector_points);
	float arclength();
	Eigen::MatrixXi intersection();
	void set_point_x(int i, int j, int coord_x);
	void set_point_y(int i, int j, int coord_y);
	int get_ptx(int i, int j);
	int get_pty(int i, int j);
	void print_Bx();
	void print_By();
	int cubic_bezier(double t,int x0,int x1,int x2,int x3);
	Eigen::MatrixXi cubic_interpolation(double t);
	Eigen::MatrixXi plot_curve(Image<cv::Vec3b> I);
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