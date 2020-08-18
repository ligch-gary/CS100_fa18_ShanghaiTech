#include <iostream>
#include "OPP_Intro/types.h"
#include "tutorial/Screen.h"
#include "tutorial/Computer.h"
#include "tutorial/Laptop.h"

using namespace std;

int main() {
    /* ********* this is test for OPP_Intro ********* */
    Triangle my_triangle(3, 4);
    Rectangle my_rectangle(3, 4);
    Circle my_circle(3);

    my_triangle.print_area_size(); // 子类继承父类，针对print_area_size函数实现了多态 (本质: 重写/override)
    my_rectangle.print_area_size();
    my_circle.print_area_size();

    /* ********* this is test for virtual funciton -- 多态 ---- ********* */
    cout<<endl;
    Shape *my_shape_ptr;
    my_shape_ptr = &my_triangle;
    my_shape_ptr->print_area_size();

    my_shape_ptr = &my_rectangle;
    my_shape_ptr->print_area_size();

    my_shape_ptr = &my_circle;
    my_shape_ptr->print_area_size();

    cout<<endl; // this is a misuse(counter) example
    Shape my_shape;
    my_shape = my_triangle;
    my_shape.print_area_size();

    my_shape = my_rectangle;
    my_shape.print_area_size();

    my_shape = my_circle;
    my_shape.print_area_size();

    cout<<endl;

    /* ********* this is test for tutorial -- Problem 1 -- ********* */
    Screen myScreen(640,480);
    cout<<"The number of pixels on my screen is: "<<myScreen.GetNumberPixels()<<endl;

    /* ********* this is test for tutorial -- Problem 2 -- ********* */
    Computer myComputer;
    cout<<"My computer's screen has "<< myComputer.GetScreen().GetNumberPixels()<<" pixels"<<endl;

    myComputer.SetScreen(myScreen);
    cout<<"My computer's screen has "<< myComputer.GetScreen().GetNumberPixels()<<" pixels"<<endl;

    /* ********* this is test for tutorial -- Problem 3 -- ********* */
    Laptop myLaptop(1000,2);
    cout<<"In powered mode, my laptop has "<< myLaptop.GetFlops(0)<<" flops"<<endl;
    cout<<"In battery mode, my laptop has "<< myLaptop.GetFlops(1)<<" flops"<<endl;

    return 0;
}