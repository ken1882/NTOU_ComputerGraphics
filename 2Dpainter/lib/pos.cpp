#include "main.h"

POS::POS(int _x, int _y){
    setPos(_x, _y);
}

void POS::setPos(int _x, int _y){
    if(_x == -1){_x = x;}
    if(_y == -1){_y = y;}
    x = _x;
    y = _y;
}

int POS::gx(){return x;}
int POS::gy(){return y;}
