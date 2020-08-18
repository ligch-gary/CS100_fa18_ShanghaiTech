//
// Created by dell on 2018/11/2.
//

#ifndef CPP_CODE_LAPTOP_H
#define CPP_CODE_LAPTOP_H

#include "Computer.h"
#include <iostream>

using namespace std;

class Laptop : public Computer {
    int m_slowDownFactor;
public:
    Laptop(int flops, int slowDownFactor);
    int GetSlowDownFactor();
    void SetSlowDownFactor( int slowDownFactor );
    int GetFlops();
    int GetFlops( int batteryMode );

};


#endif //CPP_CODE_LAPTOP_H
