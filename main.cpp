#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {

	const Image<Vec3b> B = imread("../s.jpg");

	cout << ">>> Initializing : CLIK on edge points. PRESS 0" << endl;
	VectorizationData vd = initialisation(B);

	cout << ">>> Optimizing bezigons..." << endl << endl;
	Propagation P(vd);
	P.propagate(3);

	test_compute_angles(vd);
	test_compute_energy_angles(vd);
	test_compute_bezier_handles(vd);
	test_compute_energy_data(vd);
	test_show_rms(vd);

	waitKey();
	return 0;
};

