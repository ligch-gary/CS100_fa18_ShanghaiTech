//
// Created by dell on 2018/11/2.
//

#include "Computer.h"

Screen Computer::GetScreen() {
    return m_screen;
}



void Computer::SetScreen(Screen x) {
    m_screen = x;
}


/* ************* Problem 3 overriding **************** */
void Computer::SetFlops( int flops ) {
    m_flops = flops;
}

int Computer::GetFlops() {
    return m_flops;
}

