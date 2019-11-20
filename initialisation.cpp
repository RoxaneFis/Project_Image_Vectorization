#include "Initialisation.h"

using namespace cv;
using namespace std;
using namespace Eigen;

void initialisation(Mat image){

    std::cout<<"Enter initialisation"<<std::endl;

    //Point m2(int(plot(0,0)),int(plot(0,1)));
    // MatrixXd plot = B->plot_curve(resolution);
    // cv::Mat cvT(plot.rows(),plot.cols(),CV_32FC1); 
    // eigen2cv(B_init,cvT);

    int resolution = 400;
  	
    Mat A = imread("../data/S.jpg");
    int size_image = A.rows;
    std::cout<<"Enter "<<size_image<<std::endl;

    MatrixXd B_init= MatrixXd(8,3);
    B_init.setZero();
    B_init.row(0)<< int(size_image/10),int( size_image/8), int(size_image/60);
    B_init.row(1)<< 60, 80, 100;
    B_init.row(2)<< 120, 600, 300;
    Bezier *B=new Bezier(B_init,B_init);

    for (int point = 0; point<8;point++){
      Point m1 = B->get_point(point);
      circle(A,m1,20,Scalar(0,255,0),20);
    }

    MatrixXd plot = B->plot_curve(resolution,A);
    std::cout<<plot<<std::endl;


    };





void onMouse(int event, int x, int y, int foo, void* p){
    Vector_Points* data = (Vector_Points*)p;

    if (event != EVENT_LBUTTONDOWN)
		return;
    cv::Point m1(x, y); 
    std::cout<<"Enter_on_mouse"<<std::endl;

    data->vector_points.push_back(m1);
    circle(data->image, m1, 2, Scalar(0, 255, 0), 2);
    imshow("mouse_event", data->image); 


    };



void initialisation_on_mouse(cv::Mat Image){
    std::vector<cv::Point> vector_points;
    Vector_Points data;
    data.vector_points = vector_points;
    data.image = Image;
    imshow("image", data.image);    // imshow("bezier", A);  
    cv::setMouseCallback("image", onMouse, &data);
    waitKey(0);
    std::cout<<"End"<<std::endl;
    std::cout<<vector_points[0]<<std::endl;

    // Mat image = imread("../data/S.jpg");

    //B->plot_curve(400,image);

    };




    