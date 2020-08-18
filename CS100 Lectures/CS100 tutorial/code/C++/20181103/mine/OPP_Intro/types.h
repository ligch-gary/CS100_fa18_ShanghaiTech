//
// Created by dell on 2018/11/1.
//

#ifndef CPP_CODE_TYPES_H
#define CPP_CODE_TYPES_H

#include <iostream>

using namespace std;

class Shape {
    string m_type; //1: triangle, 2: rectangle, 3:circle
    float m_base;
    float m_height;
    float m_radius;
protected:
    float get_base();
    float get_height();
    float get_radius();
    string get_type();
public:
    Shape();
    Shape(string t, float x);
    Shape(string t, float x, float y);
    ~Shape();
    void virtual print_area_size();
};

class Triangle : public Shape {
    float Triangle_base;
    float Triangle_height;
public:
//    Triangle();
    Triangle(float x, float y);
    ~Triangle();
    void T_specific();
    void print_area_size();
};

class Rectangle : public Shape {
    float Rectangle_base;
    float Rectangle_height;
public:
    Rectangle(float x, float y);
    ~Rectangle();
    void R_specific();
    void print_area_size();
};

class Circle : public Shape {
    float Circle_radius;
public:
    Circle(float x);
    ~Circle();
    void C_specific();
    void print_area_size();
};

#endif //CPP_CODE_TYPES_H
