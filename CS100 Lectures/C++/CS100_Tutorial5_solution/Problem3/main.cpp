#include <stdlib.h>
#include <stdio.h>
#include "Computer.hpp"
#include "Screen.hpp"
#include "Laptop.hpp"

int main() {
  Laptop myLaptop( 1000, 2 );
  printf( "In powered mode, my laptop has %d flops\n", myLaptop.GetFlops(0) );
  printf( "In battery mode, my laptop has %d flops\n", myLaptop.GetFlops(1) );
  return 0;
}