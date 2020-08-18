/*******************************************************
 *
 * Problem 1 consists of implementing a random-access iterator
 * into the defined HyperVector. See the homework instructions for
 * further background information on the HyperVector class. You are to modify lines
 *
 * -28 to 61: Add your implementation of the HyperVectorIterator
 * -141 and 147: Complete the implementation of the begin() and end() methods
 *  inside HyperVector, which return random-access iterators over the content
 *  of the matrix.
 * 
 *******************************************************/

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

//Important: Do not remove the following two lines
//           This is called a forward declaration, and
//           let's you use HyperVector before its actual declaration
//           has been provided.
template<class T>
class HyperVector;

template<class T>
class HyperVectorIterator : public std::iterator< std::random_access_iterator_tag, T >
{
  public:
    HyperVectorIterator(HyperVector<T> * ptr,int index){
      m_HVptr = ptr;
      m_index = index;
    }
    HyperVectorIterator(){
      m_HVptr = NULL;
      m_index = 0;
    }
    T & operator*(){
      return (*m_HVptr)[m_index];
    }
    T * operator->(){
      return &(*m_HVptr)[m_index];
    }
    T & operator[](int n){
      return (*m_HVptr)[m_index+n];
    }
    HyperVectorIterator<T> & operator++(){
      m_index++;
      return *this;
    }
    HyperVectorIterator<T> operator++(int){
      HyperVectorIterator<T> HVI;
      HVI = *this;
      ++this;
      return HVI;
    }
    HyperVectorIterator<T> & operator--(){
      m_index--;
      return *this;
    }
    HyperVectorIterator<T> operator--(int){
      HyperVectorIterator<T> HVI;
      HVI = *this;
      --this;
      return HVI;
    }
    HyperVectorIterator<T> & operator+=( int n ){
      m_index += n;
      return *this;
    }
    HyperVectorIterator<T> & operator-=( int n ){
      m_index -= n;
      return *this;
    }
    HyperVectorIterator<T> operator+( int n ) const{
      HyperVectorIterator<T> HVI;
      HVI = *this;
      HVI.m_index = m_index + n;
      return HVI;
    }
    
    HyperVectorIterator<T> operator-( int n ) const{
       HyperVectorIterator<T> HVI;
      HVI = *this;
      HVI.m_index = m_index - n;
      return HVI;
    }
    int operator-( const HyperVectorIterator<T> & that ) const{
      return m_index - that.m_index;
    } 
    bool operator== ( const HyperVectorIterator<T> & that ) const{
      return m_index == that.m_index;
    }
    bool operator!= ( const HyperVectorIterator<T> & that ) const{
      return m_index != that.m_index;
    }
    bool operator< ( const HyperVectorIterator<T> & that ) const{
      return m_index < that.m_index;
    }
    bool operator> ( const HyperVectorIterator<T> & that ) const{
      return m_index > that.m_index;
    }
    bool operator<= ( const HyperVectorIterator<T> & that ) const{
      return !(m_index > that.m_index);
    }
    bool operator>= ( const HyperVectorIterator<T> & that ) const{
      return !(m_index < that.m_index);
    }
 private:
    HyperVector<T> * m_HVptr;
    int m_index;

};
/****************
 *
 * Add your code for the (template) class HyperVectorIterator here.
 * It should inherit from the STL iterator as a random-access iterator.
 * This is required to enable the functionality of the sorting function.
 *
 * The iterator needs to override the following functions from the base-class
 *
 * T & operator*();
 * T & operator->();
 * T & operator[](int n);
 *
 * HyperVectorIterator<T> & operator++();
 * HyperVectorIterator<T> operator++(int);
 * HyperVectorIterator<T> & operator--();
 * HyperVectorIterator<T> operator--(int);
 * HyperVectorIterator<T> & operator+=( int n );
 * HyperVectorIterator<T> & operator-=( int n );
 *
 * HyperVectorIterator<T> operator-( int n ) const;
 * int operator+( const HyperVectorIterator<T> & that ) const;
 * int operator-( const HyperVectorIterator<T> & that ) const;
 * 
 * bool operator== ( const HyperVectorIterator<T> & that ) const;
 * bool operator!= ( const HyperVectorIterator<T> & that ) const;
 * bool operator< ( const HyperVectorIterator<T> & that ) const;
 * bool operator> ( const HyperVectorIterator<T> & that ) const;
 * bool operator<= ( const HyperVectorIterator<T> & that ) const;
 * bool operator>= ( const HyperVectorIterator<T> & that ) const;
 *
 ***************/

#define VALUES_PER_BUCKET  50

template<class T>
class HyperVector {
public:
  typedef HyperVectorIterator<T> iterator;

  HyperVector();
  HyperVector( size_t size, T val = T() );
  virtual ~HyperVector();

  T & operator[]( int index );
  T & at( int index );

  // The following two functions are to be implemented by yourself
  iterator begin();
  iterator end();
  size_t size();
  bool empty();
  
  void push_back( const T & elem );
  void clear();

private:
  std::vector< std::vector<T> * > m_data;
  size_t m_size;
};

template<class T>
HyperVector<T>::HyperVector() {
  m_size = 0;
}

template<class T>
HyperVector<T>::HyperVector( size_t size, T val ) {
  size_t nbrBuckets = size / VALUES_PER_BUCKET;
  m_data.reserve(nbrBuckets+1);
  for( int i = 0; i < nbrBuckets; i++ )
    m_data.push_back( new std::vector<T>(VALUES_PER_BUCKET,val) );
  if( size % VALUES_PER_BUCKET != 0 )
    m_data.push_back( new std::vector<T>(size % VALUES_PER_BUCKET,val) );
  m_size = size;
}

template<class T>
HyperVector<T>::~HyperVector() {
  for( int i = 0; i < m_data.size(); i++ )
    delete m_data[i];
}

template<class T>
T &
HyperVector<T>::operator[]( int index ) {
  return this->at(index);
}

template<class T>
T &
HyperVector<T>::at( int index ) {
  size_t mainIndex = index / VALUES_PER_BUCKET;
  size_t subIndex = index % VALUES_PER_BUCKET;

  if( !(mainIndex < m_data.size() ) ) {
    std::cout << "Error: you attempted to access an element beyond the size of the container\n";
    return (*(m_data[0]))[0];
  }

  if( !(subIndex < (*(m_data[mainIndex])).size()) ) {
    std::cout << "Error: you attempted to access an element beyond the size of the container\n";
    return (*(m_data[0]))[0];
  }

  return (*(m_data[mainIndex]))[subIndex];
}

template<class T>
typename HyperVector<T>::iterator
HyperVector<T>::begin() {
  // Todo: Implement this function to return an iterator as defined by you
  return HyperVector<T>::iterator (this,0);
}

template<class T>
typename HyperVector<T>::iterator
HyperVector<T>::end() {
  // Todo: Implement this function to return an iterator as defined by you
  return HyperVector<T> ::iterator (this,m_size);
}

template<class T>
size_t
HyperVector<T>::size() {
  return m_size;
}

template<class T>
bool
HyperVector<T>::empty() {
  return m_size == 0;
}

template<class T>
void
HyperVector<T>::push_back( const T & elem ) {
  if( m_size == 0 ) {
    m_data.push_back( new std::vector<T>() );
    m_data.back()->reserve( VALUES_PER_BUCKET );
  }

  if( m_data.back()->size() >= VALUES_PER_BUCKET ) {
    m_data.push_back( new std::vector<T>() );
    m_data.back()->reserve( VALUES_PER_BUCKET );
  }

  m_data.back()->push_back( elem );
  m_size++;
  return;
}

template<class T>
void
HyperVector<T>::clear() {
  for( int i = 0; i < m_data.size(); i++ )
    delete m_data[i];
  m_data.clear();
  m_size = 0;
}

/*************** Do not change any code below this line!! *************/

int main() {
  
  //read one line with random numbers from the console
  std::string oneLine;
  std::getline( std::cin, oneLine );
  std::stringstream lineStm(oneLine);

  //store the individual numbers of this line in a HyperVector
  HyperVector<float> vec;
  float temp;
  while( lineStm >> temp ) {
    vec.push_back( temp );
  }

  //sort the elements using the random-access iterators
  std::sort( vec.begin(), vec.end() );

  //print the result to the console
  for( int i = 0; i < vec.size(); i++ )
    std::cout << vec[i] << " ";
  std::cout << "\n";

  return 0;
}
