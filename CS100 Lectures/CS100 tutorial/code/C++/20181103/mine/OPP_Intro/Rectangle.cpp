//
// Created by dell on 2018/11/1.
//

#include "types.h"

Rectangle::Rectangle(float x, float y) : Shape("Rectangle", x, y) {
    // you can add some specific initialization of Rectangle class
    Rectangle_base = get_base();
    Rectangle_height = get_height();
}

Rectangle::~Rectangle() {

}
void Rectangle::R_specific() {
    cout<<"This is R_specific for Rectangle"<<endl;
}
void Rectangle::print_area_size() {
    float area = Rectangle_base * Rectangle_height;
    string this_type = get_type();
    cout << "The area of this type " << this_type << " is: " << area << endl;
}