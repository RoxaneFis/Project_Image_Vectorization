#include <iostream>
#include <ostream>


#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "RMS.cpp"
#include "bezier.cpp"

class Energy{
public:  
    void energy(){
        bezier();
        RMS();
        std::cout<<"enter energy"<<std::endl;
    }
};