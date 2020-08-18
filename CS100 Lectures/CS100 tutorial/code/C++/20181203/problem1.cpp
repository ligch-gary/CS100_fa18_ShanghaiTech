#include <stdlib.h>
#include <iostream>

class SharedPointerController {
public:
  SharedPointerController();

  void incrementRefCounter();
  bool decrementRefCounter();
private:
  int m_refCounter;
};

SharedPointerController::SharedPointerController() {
  m_refCounter = 0;
}

void
SharedPointerController::incrementRefCounter() {
  m_refCounter++;
}

bool
SharedPointerController::decrementRefCounter() {
  m_refCounter--;
  if( m_refCounter == 0 )
    return true;
  return false;
}

template<class T>
class SharedPointer {
public:
  SharedPointer();
  SharedPointer( T * ptr );
  SharedPointer( const SharedPointer & ptr );
  virtual ~SharedPointer();

  const SharedPointer & operator=( const SharedPointer & ptr );

  T * get();
  T & operator*();
  T * operator->();

private:
  T * m_ptr;
  SharedPointerController * m_controller;
};

template<class T>
SharedPointer<T>::SharedPointer() {
  m_ptr = NULL;
  m_controller = NULL;
}

template<class T>
SharedPointer<T>::SharedPointer( T * ptr ) {
  m_ptr = ptr;
  m_controller = new SharedPointerController();
  m_controller->incrementRefCounter();
}

template<class T>
SharedPointer<T>::SharedPointer( const SharedPointer & ptr ) {
  m_ptr = ptr.m_ptr;
  m_controller = ptr.m_controller;
  m_controller->incrementRefCounter();
}

template<class T>
SharedPointer<T>::~SharedPointer() {
  if( m_ptr != NULL ) {
    if( m_controller->decrementRefCounter() ) {
      delete m_ptr;
      delete m_controller;
    }
  }
}

template<class T>
const SharedPointer<T> &
SharedPointer<T>::operator=( const SharedPointer & ptr ) {
  if( m_ptr != NULL ) {
    if( m_controller->decrementRefCounter() ) {
      delete m_ptr;
      delete m_controller;
    }
  }

  m_ptr = ptr.m_ptr;
  m_controller = ptr.m_controller;
  m_controller->incrementRefCounter();
  return *this;
}

template<class T>
T *
SharedPointer<T>::get() {
  return m_ptr;
}

template<class T>
T &
SharedPointer<T>::operator*() {
  return *m_ptr;
}

template<class T>
T *
SharedPointer<T>::operator->() {
  return *m_ptr;
}

class TestClass {
public:
  TestClass() { std::cout << "dummy object is created\n"; }
  virtual ~TestClass() { std::cout << "dummy object is destroyed\n"; }

  void printSomething() { std::cout << "hello\n"; }
private:
  double m_dummy;
};

int main() {
  int indexA = 1;
  int indexB = 1;

  if( indexA == 1) {
    std::cout << "Entering scope A\n";
    SharedPointer<TestClass> ptrA;
    if( indexB == 1 ) {
      std::cout << "Entering scope B\n";
      SharedPointer<TestClass> ptrB( new TestClass() );
      ptrA = ptrB;
    }
    std::cout << "Returning to scope A\n";
  }
  std::cout << "Returning to global scope\n";

  return 0;
}