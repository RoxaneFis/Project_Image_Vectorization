#include "Utils.h"

using namespace cv;

std::array<cv::Point, 2> barycenters(double t, cv::Point A, cv::Point B) {
	std::array<cv::Point, 2> tab;
	if (t > 1 || t < 0) {
		std::cout << "Bad coefficient for interpolating tangents";
		throw 20;
	}
	return { (1 - t) * A + t * B,  (1 - t) * B + t * A };
}
