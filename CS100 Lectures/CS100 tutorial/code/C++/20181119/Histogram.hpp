#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

#include <stdlib.h>
#include <vector>

template<class T>
class Histogram
{
public:
  Histogram( T minVal = -1, T maxVal = 1, size_t bins = 20 );
  virtual ~Histogram();

  void insert( T val );
  size_t getRelevantBin( T val );
  void incrementRelevantBin( size_t bin, size_t increment = 1 );
  void clear();

  size_t binCount( size_t bin );
  size_t totalCount();

  T approximateMedian();

private:
  std::vector<size_t> m_bins;
  T m_binSize;
  std::vector<T> m_rightBorders;
  size_t m_totalElements;
};

#include "Histogram_impl.hpp"

#endif