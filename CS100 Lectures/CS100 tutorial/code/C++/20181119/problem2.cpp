#include <stdio.h>
#include "Timer.hpp"
#include <iostream>

// long operation to time
int dummyFunction(int n) {
  if (n < 2) {
    return n;
  } else {
    return fib(n-1) + fib(n-2);
  }
}

int main() {
  Timer timer(true);
  dummyFunction(40);
  timer.stop();

  std::cout << "fib(40) took " << timer.averageTime() << " seconds to run.\n";
}