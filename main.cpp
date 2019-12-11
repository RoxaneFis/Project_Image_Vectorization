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
	
	const Image<Vec3b> B = imread(path);
	cout << ">>> Initializing : CLIK on edge points. PRESS 0" << endl;
	VectorizationData vd = initialisation(B);
	Propagation * p = new Propagation(vd);
	p->propagate(nb_etapes, alpha, epsilon, nom);
	
	
	VectorizationData vd_2 = initialisation(B);
	Propagation * p_2 = new Propagation(vd_2);
	p->propagate(nb_etapes, alpha, epsilon, nom+to_string(2));
	cout << endl;

	//test_alpha(vd);
	//test_espilon(vd);
	//test_rms(vd);


	waitKey();
	return 0;
};

