#include <stdlib.h>
#include <stdio.h>
#include "Computer.hpp"
#include "Screen.hpp"

int main() {
  Computer myComputer;
  printf( "My computer's screen has %d pixels\n", myComputer.GetScreen().GetNumberPixels() );
  Screen myScreen(800,600);
  myComputer.SetScreen(myScreen);
  printf( "My computer's screen has %d pixels\n", myComputer.GetScreen().GetNumberPixels() );
  return 0;
}