#include "main.h"

using namespace cv;
using namespace std;
using namespace Eigen;

bool to_svg(vector<VectorizationData> vector_vd, string name) {
	std::ofstream ofs(name);
	if (!ofs.good())
		return false;
	ofs << "<?xml " << "version=\"" << "1.0" << "\" encoding=\"" << "UTF-8" << "\" standalone=\"" << "no" << "\"?>\n "
		<< "<svg " << "xmlns=\"" << "http://www.w3.org/2000/svg" << "\" version=\"" << "1.0" << "\" height=\"" << vector_vd[0].I.height() << "\" width=\"" << vector_vd[0].I.width() << "\" >\n ";
	for (int ii = 0; ii < vector_vd.size(); ii++) {
		VectorizationData vd = vector_vd[ii];
		ofs << "<path id=\"" << ii << "\" \n"
			<< "d=\"M " << vd.B.Bx.row(0)[0] << " " << vd.B.By.row(0)[0] << "\n";
		for (int jj = 0; jj < vd.B.Bx.rows(); jj++) {
			auto cp = vd.B.get_bezier(jj).control_points;
			ofs << "C " << cp[1].x << " " << cp[1].y << " "
				<< cp[2].x << " " << cp[2].y << " "
				<< cp[3].x << " " << cp[3].y << "\n";
		}
		ofs << "\"\n"
			<< "fill=\"rgb(" << (int)(vd.B.C[2]) << "," << (int)vd.B.C[1] << "," << (int)vd.B.C[0] << ")\"\n" << "/>\n";
	}
	ofs << "</svg>";
	ofs.close();
	return true;
}

int main(int argc, char* argv[]) {
	//int nb_etapes = atoi(argv[1]);
	//float alpha = atof(argv[2]);
	//float epsilon = atof(argv[3]);
	//string nom = string(argv[4]);
	//string path = string(argv[5]);

	const Image<Vec3b> I = imread("../data/heart.png");
	cout << ">>> Initializing : CLIK on edge points. PRESS 0" << endl;
	VectorizationData vd = initialisation(I);
	to_svg({ vd }, "test.svg");
	//Propagation * p = new Propagation(vd);
	//p->propagate(nb_etapes, alpha, epsilon, nom);


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


