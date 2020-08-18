#include <algorithm>
#include <memory>
#include <math.h>

template<class T>
Histogram<T>::Histogram( T minVal, T maxVal, size_t bins )
{
  m_bins.resize(bins+1,0);
  m_rightBorders.reserve(bins);
  m_binSize = (maxVal - minVal) / bins;

  for( size_t i = 0; i < bins; i++ )
    m_rightBorders.push_back(minVal + (i+1)*m_binSize);

  m_totalElements = 0;
}

template<class T>
Histogram<T>::~Histogram()
{}

template<class T>
void
Histogram<T>::Histogram::insert( T val )
{  
  size_t index = getRelevantBin(val);
  m_bins[index]++;
  m_totalElements++;
}

template<class T>
size_t
Histogram<T>::Histogram::getRelevantBin( T val )
{
  double bottomValue = m_rightBorders[0]-m_binSize;

  int index = floor( (val-bottomValue) / m_binSize );
  if( index < 0 )
    index = 0;
  if( index >= m_rightBorders.size() )
    index = m_rightBorders.size() - 1;
  return index;
}

template<class T>
void
Histogram<T>::incrementRelevantBin( size_t bin, size_t increment )
{
  m_bins[bin] += increment;
  m_totalElements += increment;
}

template<class T>
void
Histogram<T>::clear()
{
  std::fill(m_bins.begin(),m_bins.end(),0);
  m_totalElements = 0;
}

template<class T>
size_t
Histogram<T>::binCount( size_t bin )
{
  return m_bins[bin];
}

template<class T>
size_t
Histogram<T>::totalCount()
{
  return m_totalElements;
}

template<class T>
T
Histogram<T>::approximateMedian()
{
  size_t countLimit = floor(0.5f * m_totalElements + 0.5f);
  size_t count = 0;

  size_t binIndex;
  for( binIndex = 0; binIndex < m_bins.size(); binIndex++ )
  {
    count += m_bins[binIndex];
    if( count > countLimit )
      break;
  }

  if( binIndex == m_rightBorders.size() )
    return m_rightBorders.back() + m_binSize / 2.0;
  return m_rightBorders[binIndex] - m_binSize / 2.0;
}