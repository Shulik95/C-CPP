cmake_minimum_required(VERSION 3.15)
project(CPP_ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_ex1 main.cpp Matrix.cpp Dense.h Activation.cpp Dense.cpp MlpNetwork.cpp t_matrix_invalid.cpp)