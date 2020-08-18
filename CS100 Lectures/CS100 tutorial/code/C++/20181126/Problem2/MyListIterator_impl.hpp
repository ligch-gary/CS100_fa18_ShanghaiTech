template<class T>
MyListIterator<T>::MyListIterator( element_t * element, element_t * first, element_t * last ) {
  m_element = element;
  m_first = first;
  m_last = last;
}

template<class T>
MyListIterator<T>::~MyListIterator() {}

template<class T>
typename MyListIterator<T>::element_t *
MyListIterator<T>::GetPointer() {
  return m_element;
}

template<class T>
T &
MyListIterator<T>::operator*() {
  return m_element->GetElement();
}

template<class T>
MyListIterator<T> &
MyListIterator<T>::operator++() {
  if( m_first != NULL && m_last != NULL )
  {
    if( m_element != NULL )
      m_element = m_element->GetNext();
  }

  return *this;
}

template<class T>
MyListIterator<T>
MyListIterator<T>::operator++(int) {
  MyListIterator<T> retvalue = *this;
  ++(*this);
  return retvalue;
}

template<class T>
MyListIterator<T> &
MyListIterator<T>::operator--() {
  if( m_first != NULL && m_last != NULL )
  {
    if( m_element != m_first )
      m_element = m_element->GetPrevious();
  }

  return *this;
}

template<class T>
MyListIterator<T>
MyListIterator<T>::operator--(int) {
  MyListIterator<T> retvalue = *this;
  --(*this);
  return retvalue;
}

template<class T>
bool
MyListIterator<T>::operator== ( const MyListIterator<T> & that ) const {
  return m_element == that.m_element;
}

template<class T>
bool
MyListIterator<T>::operator!= ( const MyListIterator<T> & that ) const {
  return m_element != that.m_element;
}