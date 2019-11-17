#include <iostream>
#include <ostream>

#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOFF.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace Eigen;

#ifndef INCLUDE_ENTITIES
  #define INCLUDE_ENTITIES
  #include "entities.cpp"
#endif

MatrixXd B_copy;

void initialisation(){
  //test

    std::cout<<"Enter initialisation"<<std::endl;

    MatrixXd B_copy= MatrixXd(8,3);
    B_copy.setZero();
    B_copy.row(0)<< 0, 1, 2;


    std::cout<<"B_copy"<<(B_copy)<<std::endl;
    Bezier *B=new Bezier(B_copy,B_copy);
    std::cout<<"Bx"<<*(B->Bx)<<std::endl;

    //Les entites sont bien créées
    Color* C = new Color();
    Parameters W(B,C);


    std::cout<<"Test Entitities : W.B->Nb_bezigons "<<W.B->Nb_bezigons<<std::endl;
    B->set_point_x(1,1,99);
    std::cout<<"B_copy"<<(B_copy)<<std::endl;
    std::cout<<"Bx"<<*(B->Bx)<<std::endl;


    }
