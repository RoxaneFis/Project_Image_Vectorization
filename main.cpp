#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
	Propagation P;
	P.propagation();
	std::cout << "enter main" << std::endl;

	Mat B = imread("../fruits.jpg");
	imshow("Sample", B);
	waitKey();
	return 0;
};