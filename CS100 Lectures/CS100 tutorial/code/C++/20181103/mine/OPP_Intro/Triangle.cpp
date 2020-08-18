//
// Created by dell on 2018/11/1.
//

#include "types.h"

Triangle::Triangle(float x, float y) : Shape("Triangle", x, y) {
    // you can add some specific initialization of Triangle class
    Triangle_base = get_base();
    Triangle_height = get_height();
}

Triangle::~Triangle() {

}
void Triangle::T_specific() {
    cout<<"This is T_specific for Triangle"<<endl;
}
void Triangle::print_area_size() {
    float area = Triangle_base * Triangle_height * 0.5;
    string this_type = get_type();
    cout << "The area of this type " << this_type << " is: " << area << endl;
}