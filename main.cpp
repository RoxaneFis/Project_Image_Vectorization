#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {

	const Image<cv::Vec3b> B = imread("../fruits.jpg");
	//imshow("Sample", B);

	cout << ">>> Initializing vectorization ..." << endl;
	VectorizationData vd = initialisation(B);

	cout << ">>> Optimizing bezigons..." << endl << endl;
	Propagation P(vd);
	P.propagate(3);

	//test_compute_angles(vd);
	//test_compute_energy_angles(vd);
	//test_compute_bezier_handles(vd);
	test_show_rms(vd);

	waitKey();
	return 0;
};

