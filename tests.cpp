#include "Tests.h"

using namespace cv;
using namespace Eigen;


void test_compute_angles(VectorizationData vd) {
	std::cout << "TEST Angles" << std::endl;
	for (int j = 0; j < vd.B->nb_points(); j++) {
		std::array<std::vector<double>, 2> tangents_j = vd.B->get_tangents(j);
		std::vector<double> a_j = tangents_j[0];
		std::vector<double> b_j = tangents_j[1];
		double scalar_multiplication = inner_product(begin(a_j), end(a_j), begin(b_j), 0.0);
		double angle = acos(scalar_multiplication / (norm(a_j) * norm(b_j)));
		if (isnan(angle)) {
			std::cout << "The angle of point " << j << " is not defined : it may come from duplicates " << std::endl;
		}
		else {
			std::cout << "The angle of point " << j << " is (in degres) : " << angle * 380 / (2 * M_PI) << std::endl;

		}
	}
	std::cout << std::endl;

};


void test_compute_energy_angles(VectorizationData vd) {
	Energy* E = new Energy();
	std::cout << "TEST The Angles Energy is " << E->energy_angles(*vd.B) << std::endl;
	std::cout << std::endl;

};

void test_compute_bezier_handles(VectorizationData vd) {
	Energy* E = new Energy();
	std::cout << "TEST The Bezier Handles Energy is " << E->energy_bezier_handles(*vd.B) << std::endl;
	std::cout << std::endl;
};

void test_show_rms(VectorizationData vd) {
	cout << ">>> Showing rms" << endl;
	vd.B->plot_curve(vd.I);
	show_interior(vd);
};