//
// Created by dell on 2018/11/1.
//
#define PI 3.14

#include "types.h"

Circle::Circle(float x) : Shape("Circle", x) {
    // you can add some specific initialization of Circle class
    Circle_radius = get_radius();
}

Circle::~Circle() {

}

void Circle::C_specific() {
    cout<<"This is C_specific for Circle"<<endl;
}

void Circle::print_area_size() {
    float area = PI * Circle_radius * Circle_radius;
    string this_type = get_type();
    cout << "The area of this type " << this_type << " is: " << area << endl;
}