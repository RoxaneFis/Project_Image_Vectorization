#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {

	const Image<cv::Vec3b> B = imread("../fruits.jpg");
	//imshow("Sample", B);

	std::cout << "Initializing vectorization ..." << std::endl;
	VectorizationData vd = initialisation(B);
	
	test_compute_angles(vd);
	test_compute_energy_angles(vd);

	std::cout << "Optimizing bezigons..." << std::endl;
	Propagation P(vd);
	P.propagate();



	waitKey();
	return 0;
};

