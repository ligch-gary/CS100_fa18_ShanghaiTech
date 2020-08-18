#include "Computer.hpp"

Computer::Computer( int flops ) : m_screen(640,480) {
  m_flops = flops;
}

Screen
Computer::GetScreen() {
  return m_screen;
}

int
Computer::GetFlops() {
  return m_flops;
}

void
Computer::SetScreen( Screen screen ) {
  m_screen = screen;
}

void
Computer::SetFlops( int flops ) {
  m_flops = flops;
}