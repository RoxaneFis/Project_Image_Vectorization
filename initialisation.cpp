#include "Initialisation.h"

using namespace cv;
using namespace std;
using namespace Eigen;

VectorizationData initialisation(const Mat& I) {
	std::cout << "Enter initialisation" << std::endl;
	
	VectorPoints data_entered;
	data_entered.image = I;

	imshow(WINDOW_NAME, data_entered.image);
	cv::setMouseCallback(WINDOW_NAME, onMouse, (void*)&data_entered);

	Bezier* Binit = new Bezier(10);
	Color* Cinit = new Color(10);
	VectorizationData initData(Binit, Cinit, I);

	return initData;
};

void onMouse(int event, int x, int y, int flags, void* p){

	VectorPoints* userdata = (VectorPoints*)p;

	if (event == EVENT_LBUTTONDOWN)
	{
		raise(SIGINT); //for later
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		std::cout << userdata->image << std::endl;
		std::cout << userdata->vector_points << std::endl;

		Point m1(x, y);
		userdata->vector_points.push_back(m1);
		circle(userdata->image, m1, 2, Scalar(255, 0, 0), 2);
		imshow(WINDOW_NAME, userdata->image);
	}
}
