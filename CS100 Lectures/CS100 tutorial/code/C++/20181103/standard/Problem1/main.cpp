#include <stdlib.h>
#include <stdio.h>
#include "Screen.hpp"

int main() {
  Screen myScreen( 640, 480 );
  printf( "The number of pixels on my screen is %d\n", myScreen.GetNumberPixels() );
  return 0;
}