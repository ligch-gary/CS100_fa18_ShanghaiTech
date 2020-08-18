#include <stdlib.h>
#include "Histogram.hpp"
#include <iostream>

double getRandomNumber() {
  return (((double) rand())/ ((double) RAND_MAX)-0.5)*2.0;
}


int main() {
  //create a histogram
  Histogram<double> hist(-1.0,1.0,20);

  //generate 1000 random numbers and fill them into the histogram
  for( int i = 0; i < 1000; i++ )
    hist.insert(getRandomNumber());

  //get all the bin counts
  for( int i = 0; i < 20; i++ )
    std::cout << hist.binCount(i) << " ";
  std::cout << "\n\n";

  //get the median
  std::cout << hist.approximateMedian() << "\n\n";
}