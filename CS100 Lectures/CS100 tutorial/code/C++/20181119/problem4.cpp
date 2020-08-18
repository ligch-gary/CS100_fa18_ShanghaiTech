#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
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

  listTimer.sort();
  vectorTimer.sort();

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

  //print the means
  std::cout << "putting an element into a list takes in average " << listTimer.averageTime() << " seconds.\n";
  std::cout << "putting an element into a vector takes in average " << vectorTimer.averageTime() << " seconds.\n";

  //the median of the times is
  std::list<double>::iterator it3 = listTimer.begin(); for( int i = 0; i < 250; i++ ) it3++;
  std::cout << "the median time for putting an element into a list is " << *it3 << " seconds.\n";
  std::list<double>::iterator it4 = vectorTimer.begin(); for( int i = 0; i < 250; i++ ) it4++;
  std::cout << "the median time for putting an element into a vector is " << *it4 << " seconds.\n";
}