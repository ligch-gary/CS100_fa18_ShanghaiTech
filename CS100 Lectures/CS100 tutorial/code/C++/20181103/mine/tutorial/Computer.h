//
// Created by dell on 2018/11/2.
//

#ifndef CPP_CODE_COMPUTER_H
#define CPP_CODE_COMPUTER_H

#include "Screen.h"

class Computer {
    Screen m_screen;
    int m_flops;
public:
    Screen GetScreen();
    int GetFlops();
    void SetScreen(Screen x);
    void SetFlops(int x);
};


#endif //CPP_CODE_COMPUTER_H
