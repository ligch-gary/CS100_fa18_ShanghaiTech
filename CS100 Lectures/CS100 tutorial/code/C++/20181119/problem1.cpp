#include <stdlib.h>
#include <iostream>
#include <chrono>


// long operation to time
int dummyFunction(int n) {
  if (n < 2) {
    return n;
  } else {
    return fib(n-1) + fib(n-2);
  }
}


int main() {
  std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
  dummyFunction(40);
  std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

  std::chrono::high_resolution_clock::duration time = end_time - start_time;
  std::cout << "fib(40) took " <<
    std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " microsecond to run.\n";
}