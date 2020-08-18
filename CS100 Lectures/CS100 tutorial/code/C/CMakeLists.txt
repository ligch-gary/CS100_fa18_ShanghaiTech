cmake_minimum_required(VERSION 3.12)
project(C_code C)

set(CMAKE_C_STANDARD 99)
add_executable(C_code main.c tutorial/T1.c include/T1.h tutorial/T2.c include/T2.h tutorial/T3.c include/T3.h tutorial/T4.c tutorial/T4.h)
#add_executable(C_code main.c T2.c)