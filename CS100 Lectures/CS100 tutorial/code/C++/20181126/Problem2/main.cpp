#include "MyList.hpp"
#include <iostream>
#include <algorithm>
#include <vector>


int main() {

  //instantiate one of my new list object and push_back two elements
  MyList<double> myList;
  myList.push_back(0.0);
  myList.push_back(1.0);

  //use the iterator to loop through the elements and print them in the console
  MyList<double>::iterator it = myList.begin();
  while( it != myList.end() )
  {
    std::cout << *it << "\n";
    it++;
  }

  //create a standard vector and copy all the elements over
  //(exploit the fact that our iterators are also STL iterators!)
  std::vector<double> vec;
  std::copy( myList.begin(), myList.end(), std::back_inserter(vec) );

  //verify that the content has been correctly copied over to the vector
  for( int i = 0; i < vec.size(); i++ )
    std::cout << vec[i] << "\n";

  return 0;
}