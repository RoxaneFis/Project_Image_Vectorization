#include <iostream>
#include <ostream>


#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef INCLUDE_BEZIER
  #define INCLUDE_BEZIER
  #include "bezier.cpp"
#endif




void initialisation(){
        bezier();
        std::cout<<"enter initialisation"<<std::endl;
    }
