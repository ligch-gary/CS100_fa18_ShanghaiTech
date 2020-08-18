#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

class MyVector {
  friend ostream& operator<<( ostream &o, const MyVector & mv);

public:
  MyVector();
  virtual ~MyVector();

  double & at( int index );
  const double & at( int index ) const;
  void clear();
  int size() const;
  MyVector & push_back( double val );

private:
  std::vector<double> m_data;
};

MyVector::MyVector() {}

MyVector::~MyVector() {}

double &
MyVector::at( int index ) {
  return m_data[index];
}

const double &
MyVector::at( int index ) const {
  return m_data[index];
}

void
MyVector::clear() {
  m_data.clear();
}

int
MyVector::size() const {
  return m_data.size();
}

MyVector &
MyVector::push_back( double val ) {
  m_data.push_back(val);
  return *this;
}

ostream& operator<<( ostream &o, const MyVector & mv) {
  for( int i = 0; i < mv.m_data.size(); i++ )
    o << mv.m_data[i] << " ";
  o << "\n";
  return o;
}

int main() {
  MyVector mv;
  mv.push_back(1.0);
  mv.push_back(2.0);
  mv.push_back(3.0);

  cout << mv;
  return 0;
}