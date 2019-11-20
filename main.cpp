#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {

	const Mat B = imread("../fruits.jpg");
	//imshow("Sample", B);

	std::cout << "Initializing vectorization ..." << std::endl;
	vd = &initialisation(B);

	signal(SIGINT, run);

	waitKey();
	return 0;
};

void run(int signum) {
	std::cout << "Optimizing bezigons..." << std::endl;
	Propagation P(*vd);
	P.propagate();

	signal(SIGINT, run);
}