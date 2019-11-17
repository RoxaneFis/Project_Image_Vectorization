#include <iostream>
#include <ostream>


#include <igl/opengl/glfw/Viewer.h>
#include <igl/readPLY.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "initialisation.cpp"
#include "energy.cpp"

class Propagation{
public:  
    void propagation(){
        initialisation();
        Energy E;
        E.energy();
    }
};