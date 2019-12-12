#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;


int main(int argc, char* argv[]) {
	int nb_etapes = atoi(argv[1]);
	float alpha = atof(argv[2]);
	float epsilon = atof(argv[3]);
	string nom = string(argv[4]);
	string path = string(argv[5]);
	const Image<Vec3b> I = imread(path);
	cout << ">>> Initializing : CLIK on edge points. PRESS 0" << endl;
	VectorizationData vd = initialisation(I);
	Propagation * p = new Propagation(vd);
	p->propagate(nb_etapes, alpha, epsilon, nom);
	cout<<"fin_main"<<endl;

	// Bezier bez1(Point2d(10, 100), Point2d(90, 30), Point2d(40, 140), Point2d(220, 220));
	// Bezier bez2(Point2d(5, 150), Point2d(180, 20), Point2d(80, 250), Point2d(210, 190));
	// vector<array<double, 2>> vector_ts = intersect(bez1, bez2);
	// for (auto ts : vector_ts) {
	// 	cout << "t bez 1 : " << ts[0] << " , t bez 2 : " << ts[1] << endl;
	// }

	// VectorizationData vd_2 = initialisation(B);
	// Propagation * p_2 = new Propagation(vd_2);
	// p->propagate(nb_etapes, alpha, epsilon, nom+to_string(2));
	// cout << endl;

	//test_alpha(vd);
	//test_espilon(vd);
	//test_rms(vd);


	waitKey();
	return 0;
};


