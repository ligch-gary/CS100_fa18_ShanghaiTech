//
// Created by dell on 2018/11/2.
//

#include "Laptop.h"
Laptop::Laptop(int x, int y) {
    SetFlops(x);
    m_slowDownFactor = y;
}

int Laptop::GetSlowDownFactor() {
    return m_slowDownFactor;
}

void Laptop::SetSlowDownFactor(int y) {
    m_slowDownFactor = y;
}

// access the original GetFlops from the base class
int Laptop::GetFlops() {
    return Computer::GetFlops();
}


int Laptop::GetFlops( int batteryMode ){
    if(batteryMode==0){
        return GetFlops();
    } else if(batteryMode==1) {
        return GetFlops()/m_slowDownFactor;
    } else{
        cout<<"error!"<<endl;
        return 0;
    }
}
