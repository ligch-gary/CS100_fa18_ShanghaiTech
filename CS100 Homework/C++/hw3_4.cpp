#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#define pi 3.1415926
using namespace std;
class Shape{
    public:
        virtual void OutputArea(){}
        virtual void OutputPerimeter(){}
        virtual void OutputNumberCorners(){}
    protected:
        float x,y,z;
};
class Rectangle : public Shape{
    public:
    Rectangle(){
        x = y = 0;
    }
    Rectangle(float size1,float size2){
        x = size1;
        y = size2;
    }
    virtual void OutputArea(){
        std :: cout << "Area: "<< x*y << endl;   
    }
    virtual void OutputPerimeter(){
        std :: cout << "Perimeter: " << 2*x+2*y << endl;
    }
    virtual void OutputNumberCorners(){
        std :: cout << "Corners: 4"<< endl;
    }
};
class Square : public Shape {
    public:
    Square(){
        x = y = 0;
    }
    Square(float size1){
        x = size1;
        y = size1;
    }
    virtual void OutputArea(){
        std :: cout << "Area: "<< x*y << endl;   
    }
    virtual void OutputPerimeter(){
        std :: cout << "Perimeter: " << 2*x+2*y << endl;
    }
    virtual void OutputNumberCorners(){
        std :: cout << "Corners: 4"<< endl;
    }
};
class Triangle : public Shape {
    public:
    Triangle(){
        x = y = 0;
    }
    Triangle(float size1,float size2){
        x = size1;
        y = size2;
    }
    virtual void OutputArea(){
        std :: cout << "Area: "<< x*y/2.0 << endl;   
    }
    virtual void OutputPerimeter(){
        std :: cout << "Perimeter: " << x + y + sqrt(x*x+y*y) << endl;
    }
    virtual void OutputNumberCorners(){
        std :: cout << "Corners: 3"<< endl;
    }
};
class Circle : public Shape {
    public:
    Circle(){
        x = 0;
    }
    Circle(float size1){
        x = size1;
    }
    virtual void OutputArea(){
        std :: cout << "Area: "<< pi*x*x << endl;   
    }
    virtual void OutputPerimeter(){
        std :: cout << "Perimeter: " << 2*pi*x << endl;
    }
    virtual void OutputNumberCorners(){
        std :: cout << "Corners: 0"<< endl;
    }
};
int main() {
 std::list<Shape*> shapeDatabase;
 while(1) {
std::cout << "Enter a type (Circle, Triangle, Square, or Rectangle) ";
std::cout << "and one or two size parameters, ";
std::cout << "separated with blank spaces:\n";
 float size1;
 float size2;
 std::string shapeType;
 std::cin >> shapeType;
 if( shapeType == std::string("Circle") ) {
 std::cin >> size1;
 shapeDatabase.push_back( new Circle( size1 ) );
 }
 else if ( shapeType == std::string("Triangle") ) {
 std::cin >> size1 >> size2;
 shapeDatabase.push_back( new Triangle(size1,size2) );
 }
 else if ( shapeType == std::string("Square") ) {
 std::cin >> size1;
 shapeDatabase.push_back( new Square(size1) );
 }
 else if (shapeType == std::string("Rectangle") ) {
 std::cin >> size1 >> size2;
 shapeDatabase.push_back( new Rectangle(size1,size2) );
 }
 else {
 std::cout << "Unrecognized shape!!\n";
 }
 std::cout << "Do you want to add more shapes? (Enter Y or N)\n";
 std::string answer;
 std::cin >> answer;
 if( answer != std::string("Y") )
 break;
 }
 std::list<Shape *>::iterator it = shapeDatabase.begin();
 int shapeCounter = 0;
 while( it != shapeDatabase.end() )
 {
 std::cout << "Properties of shape " << shapeCounter++ << ":\n";
 (*it)->OutputArea();
 (*it)->OutputPerimeter();
 (*it)->OutputNumberCorners();
 it++;
 }
 return 0;
}


