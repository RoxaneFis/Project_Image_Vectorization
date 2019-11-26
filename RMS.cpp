#include "RMS.h"

using namespace std;
using namespace Eigen;

void rms() {
	std::cout << "enter RMS" << std::endl;
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
	int m00 = pow(2, s) * phi_s_k(x, s, kx)* phi_s_k(y, s, ky);
	int m01 = pow(2, s) * phi_s_k(x, s, kx) * psi_s_k(y, s, ky);
	int m10 = pow(2, s) * psi_s_k(x, s, kx) * phi_s_k(y, s, ky);
	int m11 = pow(2, s) * psi_s_k(x, s, kx) * psi_s_k(y, s, ky);
	m << m00, m01,
		m10, m11;
	return m;
};
