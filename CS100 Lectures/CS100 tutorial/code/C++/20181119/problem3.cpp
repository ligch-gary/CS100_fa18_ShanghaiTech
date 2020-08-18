#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include "Timer.hpp"

class LargeObject {
public:
  LargeObject();
  virtual ~LargeObject();

private:
  int m_data[1000000];
};

LargeObject::LargeObject() {};
LargeObject::~LargeObject() {};


int main() {
  LargeObject obj;

  //create a list and a timer for the list
  std::list<LargeObject> myList;
  Timer listTimer;
  for( int i = 0; i < 500; i++ ) {
    listTimer.start();
    myList.push_back(obj);
    listTimer.stop();
  }

  //create a vector and a timer for the vector
  std::vector<LargeObject> myVector;
  Timer vectorTimer;
  for( int i = 0; i < 500; i++) {
    vectorTimer.start();
    myVector.push_back(obj);
    vectorTimer.stop();
  }

  //print all times for the list
  std::cout << "The times for the list are:\n";
  std::list<double>::iterator it1 = listTimer.begin();
  while( it1 != listTimer.end() ) {
    std::cout << *it1 << " "; it1++;
  }
  std::cout << "\n\n";

  //print all times for the vector
  std::cout << "The times for the vector are:\n";
  std::list<double>::iterator it2 = vectorTimer.begin();
  while( it2 != vectorTimer.end() ) {
    std::cout << *it2 << " "; it2++;
  }
  std::cout << "\n\n";
}