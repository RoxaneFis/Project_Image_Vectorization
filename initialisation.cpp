#include "Initialisation.h"

using namespace cv;
using namespace std;
using namespace Eigen;

VectorizationData initialisation(Image<Vec3b> I) {
	VectorPoints data;
	data.image = I;
	vector<Point>* vector_points = new vector<Point>;
	data.vector_points = vector_points;

	resizeWindow(WINDOW_NAME, 600, 600);
	namedWindow(WINDOW_NAME, WINDOW_NORMAL);
	setMouseCallback(WINDOW_NAME, onMouse, &data);
	imshow(WINDOW_NAME, data.image);
	waitKey(0);
	cout << vector_points->size() << " points have been entered" << endl;

	Bezigon firstBezigon = Bezigon(*vector_points);
	firstBezigon.plot_curve(I, "Initialisation");

	VectorizationData initData = VectorizationData(firstBezigon, I);
	return initData;
};

void onMouse(int event, int x, int y, int flags, void* p) {

	VectorPoints* data = (VectorPoints*)p;

	if (event == EVENT_LBUTTONDOWN)
	{
		Point m1(x, y);
		Point end;

		if (data->vector_points->size() == 0) {
			cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
			data->vector_points->push_back(m1);
		}
		else {
			end = (*(data->vector_points)).back();
			if (end != m1) {
				cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
				data->vector_points->push_back(m1);
			}
			else { cout << "Please enter another point" << endl; }
		}
		circle(data->image, m1, 1, Scalar(255, 0, 0), 2);
		resizeWindow(WINDOW_NAME, 600, 600);
		imshow(WINDOW_NAME, data->image);
	}
}
