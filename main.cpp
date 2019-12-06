#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {

	const Image<Vec3b> B = imread("../data/fruits.jpg");

	cout << ">>> Initializing : CLIK on edge points. PRESS 0" << endl;
	VectorizationData vd = initialisation(B);
	cout << "Bx" << endl;
	cout << vd.B.Bx << endl;
	cout << endl;

	test_rms(vd);

	waitKey();
	return 0;
};

