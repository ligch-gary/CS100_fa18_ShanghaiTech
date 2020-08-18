#ifndef MYLIST_HPP_
#define MYLIST_HPP_

#include <stdlib.h>
#include "DoublyLinkedElement.hpp"
#include "MyListIterator.hpp"

//This is the main class for our custom list
//It defines a few convenience types at the beginning (iterator and element)
//The rest is basically just the functions that need to be executed
//The most important thing to realize is that the list should have two member pointers
//-One is the first element in the list
//-One is the last element in the list
//This allows for both efficient access to both the back and the front of the list


template<class T>
class MyList {
public:
  typedef MyListIterator<T> iterator;
  typedef DoublyLinkedElement<T> element;

  MyList();
  virtual ~MyList();

  iterator begin();
  iterator end();
  size_t size();
  bool empty();
  
  void erase(iterator it);
  void insert(iterator it, const T & value);
  
  void push_back( const T & elem );
  void clear();

private:
  size_t m_size;
  element * m_first;
  element * m_last;
};

#include "MyList_impl.hpp"

#endif