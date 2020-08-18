#ifndef COMPUTER_HPP_
#define COMPUTER_HPP_

#include <stdlib.h>
#include "Screen.hpp"

class Computer {
public:
  Computer();

  Screen GetScreen();
  void SetScreen( Screen screen );

private:
  Screen m_screen;
};

#endif