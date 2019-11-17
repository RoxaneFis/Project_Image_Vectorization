
cmake_minimum_required(VERSION 3.1)
PROJECT(code_Image_Vectorization)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#OpenCV
SET(OpenCV_STATIC OFF)
FIND_PACKAGE(OpenCV REQUIRED QUIET)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

# libigl
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
find_package(LIBIGL REQUIRED QUIET)


INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
add_executable(main main.cpp)
target_link_libraries(main igl::core igl::opengl_glfw)
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})





