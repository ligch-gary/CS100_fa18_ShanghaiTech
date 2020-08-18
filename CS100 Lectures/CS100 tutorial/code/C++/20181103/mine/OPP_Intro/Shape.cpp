//
// Created by dell on 2018/11/1.
//

#include "types.h"

//父类的多种构造函数-->单个class内部的多态， (本质: 重载/overload)
Shape::Shape(string t, float x, float y) {
    m_type = t; //1: triangle, 2: rectangle
    m_base = x;
    m_height = y;
    m_radius = 0;
}

Shape::Shape(string t, float x) {
    m_type = t; // 3:circle
    m_radius = x;
    m_base = 0;
    m_height = 0;

}
Shape::Shape() {
    m_type = -1; // 3:circle
    m_radius = 0;
    m_base = 0;
    m_height = 0;

}
Shape::~Shape() {

}

string Shape::get_type() {
    return m_type;
}

float Shape::get_base() {
    return m_base;
}

float Shape::get_height() {
    return m_height;
}

float Shape::get_radius() {
    return m_radius;
}

void Shape::print_area_size() {
    cout << "This is Shape print_area_size."<<endl;
}
