#include "main.h"

#ifndef INCLUDE_POLYGON
#define INCLUDE_POLYGON
struct _Polygon:public Drawable{
    using Drawable::x;
    using Drawable::y;
    using Drawable::color;

    int width, height;
    _Polygon(int _x, int _y, int _w, int _h);
    _Polygon(int _x, int _y, int _w, int _h, Color*);
    _Polygon(int _x, int _y, int _w, int _h, Color**);
    void draw(int);
    void resize(int, int);
};

#endif // INCLUDE_POLYGON
