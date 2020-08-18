#ifndef DOUBLYLINKEDELEMENT_HPP_
#define DOUBLYLINKEDELEMENT_HPP_

#include <stdlib.h>

//This class wraps around an element of generic type T
//It also adds two pointers
//-One to the previous (wrapped) element
//-One to the next (wrapped) element

template<class T>
class DoublyLinkedElement {
public:
  DoublyLinkedElement( const T & element, DoublyLinkedElement<T> * previous, DoublyLinkedElement<T> * next );
  virtual ~DoublyLinkedElement();

  T & GetElement();

  DoublyLinkedElement<T> * GetPrevious();
  DoublyLinkedElement<T> * GetNext();
  void SetPrevious( DoublyLinkedElement<T> * m_previous );
  void SetNext( DoublyLinkedElement<T> * m_next );
  
private:
  T m_element;
  DoublyLinkedElement<T> * m_previous;
  DoublyLinkedElement<T> * m_next;
};

#include "DoublyLinkedElement_impl.hpp"

#endif