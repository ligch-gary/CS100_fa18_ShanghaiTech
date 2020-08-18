cmake_minimum_required(VERSION 3.12)
project(CPP_code)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP_code main.cpp OPP_Intro/Shape.cpp OPP_Intro/Rectangle.cpp OPP_Intro/Circle.cpp OPP_Intro/Triangle.cpp OPP_Intro/types.h tutorial/Screen.cpp tutorial/Screen.h tutorial/types.h tutorial/Computer.cpp tutorial/Computer.h tutorial/Laptop.cpp tutorial/Laptop.h)