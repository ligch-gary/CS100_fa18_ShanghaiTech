#include "Computer.hpp"

Computer::Computer() : m_screen(640,480) {
}

Screen
Computer::GetScreen() {
  return m_screen;
}

void
Computer::SetScreen( Screen screen ) {
  m_screen = screen;
}