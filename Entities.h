#pragma once

#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

#include "Image.h"
#include "Utils.h"

class Bezier
{
private:
	const int plot_resolution = 50;
	const int dim = 2;
	Eigen::MatrixXd* Bx;
	Eigen::MatrixXd* By;

public:
	int Nb_bezigons;
	Bezier(int N);
	Bezier(const Eigen::MatrixXd& B_x, const Eigen::MatrixXd& B_y);
	Bezier(const std::vector<cv::Point>& vector_points);
	std::array<std::vector<double>,2> get_tangents(int j);
	float arclength();
	int nb_points();
	Eigen::MatrixXd intersection();
	void set_point_x(int i, int j, double coord_x);
	void set_point_y(int i, int j, double coord_y);
	double get_ptx(int i, int j);
	double get_pty(int i, int j);
	void print_Bx();
	void print_By();
	double cubic_bezier(double t,int x0,int x1,int x2,int x3);
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