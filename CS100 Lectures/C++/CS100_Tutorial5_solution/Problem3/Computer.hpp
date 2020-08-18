#ifndef COMPUTER_HPP_
#define COMPUTER_HPP_

#include <stdlib.h>
#include "Screen.hpp"

class Computer {
public:
  Computer( int flops );

  Screen GetScreen();
  int GetFlops();
  void SetScreen( Screen screen );
  void SetFlops( int flops );

private:
  Screen m_screen;
  int m_flops;
};

#endif