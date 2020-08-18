//
// Created by dell on 2018/11/2.
//

#include "Screen.h"
Screen::Screen() {
    m_width = 0;
    m_height = 0;
}

Screen::Screen(int x, int y) {
    m_width = x;
    m_height = y;
}

int Screen::GetHeight() {
    return m_height;
}

int Screen::GetWidth() {
    return m_width;
}

void Screen::SetWidth(int x) {
    m_width = x;
}

void Screen::SetHeight(int y) {
    m_height = y;
}

int Screen::GetNumberPixels() {
    return m_width*m_height;
}
