#ifndef MYLISTITERATOR_HPP_
#define MYLISTITERATOR_HPP_

#include <stdlib.h>
#include <iterator>
#include "DoublyLinkedElement.hpp"

template<class T>
class MyListIterator : public std::iterator< std::bidirectional_iterator_tag, T> {
public:
  typedef DoublyLinkedElement<T> element_t;

  MyListIterator( element_t * element, element_t * first, element_t * last );
  virtual ~MyListIterator();

  element_t * GetPointer();
  T & operator*();

  MyListIterator<T> & operator++();
  MyListIterator<T> operator++(int);
  MyListIterator<T> & operator--();
  MyListIterator<T> operator--(int);

  bool operator== ( const MyListIterator<T> & that ) const;
  bool operator!= ( const MyListIterator<T> & that ) const;

private:
  element_t * m_element;
  element_t * m_first;
  element_t * m_last;
};

#include "MyListIterator_impl.hpp"

#endif