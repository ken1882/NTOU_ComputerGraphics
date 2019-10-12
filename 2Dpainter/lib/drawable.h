#include "main.h"

#ifndef INCLUDE_DRAWABLE
#define INCLUDE_DRAWABLE

const int DW_CLEAR_BIT = 16;    // Clean canvas bit position
const int DW_FLUSH_BIT = 17;    // Flush canvas bit position
const int DW_CLEAR = 1 << DW_CLEAR_BIT;
const int DW_FLUSH = 1 << DW_FLUSH_BIT;

// drawable.cpp
struct Drawable:public POS{
    using POS::x;
    using POS::y;

    float anchor;   // object drawing anchor
    Color* color;   // color of the draw

    Drawable(int _x = 0, int _y = 0);
    Drawable(int _x, int _y, Color*);
    Drawable(int _x, int _y, Color**);
    ~Drawable();

    // Proc: lambda where drawing procedure is executed
    template <typename Proc>
    void draw(int mask, Proc p){
        float r = color -> r;
        float g = color -> g;
        float b = color -> b;
        int mode   = mask & 0xffff;
        bool fclear = Util::get_bit_mask(mask, DW_CLEAR_BIT);
        bool fflush = Util::get_bit_mask(mask, DW_FLUSH_BIT);
        if(fclear){
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glColor3f(r, g, b);
        glBegin(mode);
        p(x, y);
        glEnd();
        if(fflush){glFlush();}
    }
};



#endif // INCLUDE_DRAWABLE
