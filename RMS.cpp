#include "RMS.h"

using namespace std;
using namespace Eigen;
using namespace cv;

void rms() {

};

int psi(double t) {
	if (t < 0 || t >= 1) return 0;
	else return (t < 1 / 2) ? 1 : -1;
}

int phi(double t) {
	return (t < 0 || t >= 1) ? 0 : 1;
}

int psi_s_k(double t, int s, int k) {
	return psi(pow(2, s) * t - k);
};

int phi_s_k(double t, int s, int k) {
	return phi(pow(2, s) * t - k);
};

Matrix2i haar(int s, int kx, int ky, double x, double y) {
	MatrixXi m(2, 2);
	int m00 = pow(2, s) * phi_s_k(x, s, kx) * phi_s_k(y, s, ky);
	int m01 = pow(2, s) * phi_s_k(x, s, kx) * psi_s_k(y, s, ky);
	int m10 = pow(2, s) * psi_s_k(x, s, kx) * phi_s_k(y, s, ky);
	int m11 = pow(2, s) * psi_s_k(x, s, kx) * psi_s_k(y, s, ky);
	m << m00, m01,
		m10, m11;
	return m;
};

bool is_interior(Point p, MatrixXi curve) {
	// first method to tell if a point is inside a curve (supposing the last point of the matrix is linked to the first one)
	int count = 0;
	int nb_points = curve.rows();
	int min_y = curve.colwise().minCoeff()[1];
	int max_y = curve.colwise().maxCoeff()[1];
	if (min_y == p.y || max_y == p.y) return false; // to get rid of the corners and not count on the line
	for (size_t ii = 0; ii < nb_points - 1; ii++) {
		if ((curve.row(ii)[1] - p.y) * (curve.row(ii + 1)[1] - p.y) <= 0
			&& (curve.row(ii + 1)[1] - p.y) != 0
			&& curve.row(ii + 1)[0] < p.x
			&& curve.row(ii)[0] < p.x) {
			count++;
		};
	}
	if ((curve.row(nb_points - 1)[1] - p.y) * (curve.row(0)[1] - p.y) <= 0
		&& (curve.row(0)[1] - p.y) != 0
		&& curve.row(0)[0] < p.x
		&& curve.row(nb_points - 1)[0] < p.x) {
		count++;
	};
	return count % 2 == 1;
};


Image<Vec3b> get_rasterized(VectorizationData vd) {
	Vec3b white = { 255,255,255 };
	Vec3b black = { 0,0,0 };

	Vec3f aux_color = { 0,0,0 };
	Vec3b color = { 0,0,255 };

	Image<Vec3b> I_int(vd.I.width(), vd.I.height());
	MatrixXi curve = vd.B->get_sample_points();
	int count_int = 0;
	for (size_t xx = 0; xx < vd.I.width(); xx++) {
		for (size_t yy = 0; yy < vd.I.height(); yy++) {
			if (is_interior(Point(xx, yy), curve)) {
				I_int(xx, yy) = black;
				count_int++;
				aux_color += vd.I(xx, yy);
			}
			else {
				I_int(xx, yy) = white;
			}
		}
	};
	color = aux_color / count_int;
	for (size_t xx = 0; xx < vd.I.width(); xx++) {
		for (size_t yy = 0; yy < vd.I.height(); yy++) {
			if (I_int(xx, yy) == black) {
				I_int(xx, yy) = color;
			}
		}
	};

	return I_int;

}
void show_interior(VectorizationData vd) {
	Image<Vec3b> I_int = get_rasterized(vd);
	imshow("Rasterized Image", I_int);
}


