template<class T>
MyList<T>::MyList() {
  //whenever the list is empty, the first and last need to point to NULL
  m_first = NULL;
  m_last = NULL;
  m_size = 0;
}

template<class T>
MyList<T>::~MyList() {
  //do not forget to clear the list before destruction to free the heap
  clear();
}

template<class T>
typename MyList<T>::iterator
MyList<T>::begin() {
  //pass a pointer to the beginning to iterator
  //the iterator also needs to know the first and the last element, otherwise this is useless
  return iterator(m_first,m_first,m_last);
}

template<class T>
typename MyList<T>::iterator
MyList<T>::end() {
  //pass a NULL pointer, by which we characterize the end-iterator (one past the last element)
  return iterator(NULL,m_first,m_last);
}

template<class T>
size_t
MyList<T>::size() {
  return m_size;
}

template<class T>
bool
MyList<T>::empty() {
  return m_size == 0;
}

template<class T>
void
MyList<T>::erase(iterator it) {
  //first check that the list is not empty and that the iterator is valid
  if( !empty() && it.GetPointer() != NULL ) {
    //if there is only one element in the list, keep it simple
    if( size() == 1 ) {
      clear();
    }
    else {
      //if there are more elements, there are a few cases to distinguish
      if( it.GetPointer() == m_first ) { //the first element is to be deleted
        element * newFirst = m_first->GetNext();
        delete m_first;
        m_first = newFirst;
        //do not forget to reset the pointer to the previous element for the new first element to NULL
        m_first->SetPrevious(NULL);
      }
      else if( it.GetPointer() == m_last ) { //the last element is to be deleted
        element * newLast = m_last->GetPrevious();
        delete m_last;
        m_last = newLast;
        //do not forget to cancel the pointer to the next element for the new last element in the list to NULL
        m_last->SetNext(NULL);
      }
      else { //some random element is to be deleted
        element * previous = it.GetPointer()->GetPrevious();
        element * next = it.GetPointer()->GetNext();
        delete it.GetPointer();
        //both the pointer to the next element of the element before and the pointer to the previous element of the one after need to be reset
        previous->SetNext(next);
        next->SetPrevious(previous);
      }
      m_size--;
    }
  }
}

template<class T>
void
MyList<T>::insert(iterator it, const T & value) {
  if( empty() && it.GetPointer() == NULL ) {
    //there is nothing in the list, so simply add this element
    element * newElement = new element(value,NULL,NULL);
    m_first = newElement;
    m_last = newElement;
  }
  else {
    if( it.GetPointer() == NULL ) {
      //end of the list
      element * newElement = new element(value,m_last,NULL);
      m_last->SetNext(newElement);
      m_last = newElement;
    }
    else {
      //somewhere inside the list
      element * newElement = new element(value,it.GetPointer()->GetPrevious(),it.GetPointer());
      it.GetPointer()->GetPrevious()->SetNext(newElement);
      it.GetPointer()->SetPrevious(newElement);
    }
  }
  m_size++;
}

template<class T>
void
MyList<T>::push_back( const T & elem ) {
  switch( size() )
  {
    case 0: //nothing in the list yet, so simply add
      m_first = new element( elem, NULL, NULL );
      m_last = m_first;
      m_size = 1;
      break;
    default: //add to the back of the list
      element * oldLast = m_last;
      m_last = new element( elem, oldLast, NULL );
      oldLast->SetNext( m_last );
      m_size++;
      break;
  }
}

template<class T>
void
MyList<T>::clear() {
  //delete the current element as long as there is something left in the list
  element * current = m_first;
  while( current != NULL )
  {
    element * next = current->GetNext();
    delete current;
    current = next;
  }

  //set all pointers to zero and the size as well
  m_size = 0;
  m_first = NULL;
  m_last = NULL;
}