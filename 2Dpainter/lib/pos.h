#include "main.h"

#ifndef INCLUDE_POS
#define INCLUDE_POS
struct POS{
    POS(int _x = 0,int _y = 0);
    int x, y;
    void setPos(int,int);
    int gx();
    int gy();
};
#endif // INCLUDE_POS
