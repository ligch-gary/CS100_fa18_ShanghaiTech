#include "Screen.hpp"

Screen::Screen( int width, int height ) {
  SetWidth( width );
  SetHeight( height );
}

int
Screen::GetWidth() {
  return m_width;
}

int
Screen::GetHeight() {
  return m_height;
}

void
Screen::SetWidth( int width ) {
  m_width = width;
}

void
Screen::SetHeight( int height ) {
  m_height = height;
}

int
Screen::GetNumberPixels() {
  return m_width * m_height;
}