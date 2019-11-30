#include "Initialisation.h"

using namespace cv;
using namespace std;
using namespace Eigen;

VectorizationData initialisation(Image<cv::Vec3b> I) {

	VectorPoints data;
	data.image = I;
	vector<Point> *vector_points = new vector<Point>;

	data.vector_points = vector_points;
	
	namedWindow(WINDOW_NAME, 1);
	setMouseCallback(WINDOW_NAME, onMouse, &data);
	imshow(WINDOW_NAME, data.image);
	waitKey(0);
	std::cout << vector_points->size()<<" points have been entered" << std::endl;
	std::cout << std::endl;

	//Add the first point at the end to loop
	//vector_points->push_back((*vector_points)[0]);
	Bezier* Binit = new Bezier(*vector_points);

	std::array<std::vector<double>,2> tange = Binit->get_tangents(1);
	Color* Cinit = new Color(10);
	VectorizationData initData(Binit, Cinit, I);

	return initData;
};

void onMouse(int event, int x, int y, int flags, void* p){

	VectorPoints* data = (VectorPoints*)p;

	if (event == EVENT_LBUTTONDOWN)
	{
		Point m1(x, y);
		Point end;

		if(data->vector_points->size()==0){
			cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
			data->vector_points->push_back(m1);
		}
		else{
			end = (*(data->vector_points)).back();
			if(end!=m1){
				cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
				data->vector_points->push_back(m1);}
			else{cout<<"Please enter another point"<<endl;}
			}
		circle(data->image, m1, 1, Scalar(255, 0, 0), 2);
		imshow(WINDOW_NAME, data->image);
	}
}
