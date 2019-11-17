#include <iostream>
#include <ostream>
#include <fstream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "propagation.cpp"

using namespace cv;
using namespace std;
using namespace Eigen;


int main(int argc, char *argv[]){
    Propagation P;
    P.propagation();
    std::cout<<"enter main"<<std::endl;

    Mat B = imread("../fruits.jpg");
    imshow("Sample", B);
    waitKey();  
    return 0;
}