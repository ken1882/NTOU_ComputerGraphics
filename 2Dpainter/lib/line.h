#include "main.h"

#ifndef INCLUDE_LINE
#define INCLUDE_LINE
struct Line:public Drawable{
    using Drawable::x;
    using Drawable::y;
    using Drawable::color;

    int line_width, x2, y2;
    Line(int, int, int, int, int);
    Line(int, int, int, int, int, Color*);
    Line(int, int, int, int, int, Color**);
    void init(int,int,int);
    void setDest(int, int);
    void draw(int);
};

#endif // INCLUDE_LINE
