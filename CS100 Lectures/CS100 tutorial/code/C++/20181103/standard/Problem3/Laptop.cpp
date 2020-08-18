#include "Laptop.hpp"

Laptop::Laptop( int flops, int slowDownFactor ) : Computer(flops) {
  m_slowDownFactor = slowDownFactor;
}

int
Laptop::GetSlowDownFactor() {
  return m_slowDownFactor;
}

void
Laptop::SetSlowDownFactor( int slowDownFactor ) {
  m_slowDownFactor = slowDownFactor;
}

int
Laptop::GetFlops() {
  return Computer::GetFlops();
}

int
Laptop::GetFlops( int batteryMode ) {
  if( batteryMode )
    return GetFlops() / m_slowDownFactor;
  return GetFlops();
}