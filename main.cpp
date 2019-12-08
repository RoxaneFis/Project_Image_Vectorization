#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {

	const Image<Vec3b> B = imread("../data/red.jpg");

	cout << ">>> Initializing : CLIK on edge points. PRESS 0" << endl;
	VectorizationData vd = initialisation(B);
	Propagation * p = new Propagation(vd);
	p->propagate(2,0.00001, 4);
	cout << endl;

	//test_rms(vd);

	waitKey();
	return 0;
};

