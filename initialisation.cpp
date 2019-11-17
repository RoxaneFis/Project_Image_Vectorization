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

MatrixXd B_init;

void initialisation(){

    std::cout<<"Enter initialisation"<<std::endl;

    MatrixXd B_init= MatrixXd(8,3);
    B_init.setZero();
    B_init.row(0)<< 0, 1, 2;


    Bezier *B=new Bezier(B_init,B_init);
    //std::cout<<"B_init"<<(B_init)<<std::endl;
    //std::cout<<"Bx"<<*(B->Bx)<<std::endl;

    //Les entites sont bien créées
    Color* C = new Color(6);
    Parameters W(B,C);
    //std::cout<<"Test Entitities : W.B->Nb_bezigons "<<W.B->Nb_bezigons<<std::endl;

    //CHANGE W -> CHANGE C
    W.C->setColor(1,1,5);
    //C->print_Matrix();


    B->set_point_x(1,1,99);
    //B_init nest pas modifie
    //std::cout<<"B_init"<<(B_init)<<std::endl;
    //std::cout<<"Bx"<<*(B->Bx)<<std::endl;


    }
