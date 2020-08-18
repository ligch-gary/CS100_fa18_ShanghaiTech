template<class T>
DoublyLinkedElement<T>::DoublyLinkedElement( const T & element, DoublyLinkedElement<T> * previous, DoublyLinkedElement<T> * next ) {
  m_element = element;
  m_previous = previous;
  m_next = next;
}

template<class T>
DoublyLinkedElement<T>::~DoublyLinkedElement() {}

template<class T>
T &
DoublyLinkedElement<T>::GetElement() {
  return m_element;
}

template<class T>
DoublyLinkedElement<T> *
DoublyLinkedElement<T>::GetPrevious() {
  return m_previous;
}

template<class T>
DoublyLinkedElement<T> *
DoublyLinkedElement<T>::GetNext() {
  return m_next;
}

template<class T>
void
DoublyLinkedElement<T>::SetPrevious( DoublyLinkedElement<T> * previous ) {
  m_previous = previous;
}

template<class T>
void
DoublyLinkedElement<T>::SetNext( DoublyLinkedElement<T> * next ) {
  m_next = next;
}