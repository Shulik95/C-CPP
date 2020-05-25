cmake_minimum_required(VERSION 3.15)
project(C_project3 C)

set(CMAKE_C_STANDARD 99)

add_executable(C_project3 RBTree.c Structs.h RBTree.h Structs.c ProductExample.c)