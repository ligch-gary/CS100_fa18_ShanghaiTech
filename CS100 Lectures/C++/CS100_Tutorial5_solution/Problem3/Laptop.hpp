#ifndef LAPTOP_HPP_
#define LAPTOP_HPP_

#include <stdlib.h>
#include "Computer.hpp"

class Laptop : public Computer {
public:
  Laptop( int flops, int slowDownFactor );

  int GetSlowDownFactor();
  void SetSlowDownFactor( int slowDownFactor );

  int GetFlops();
  int GetFlops( int batteryMode );

private:
  int m_slowDownFactor;
};

#endif