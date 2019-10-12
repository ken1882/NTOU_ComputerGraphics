#include "main.h"

_Polygon::_Polygon(int _x, int _y, int _w, int _h):
    Drawable(_x, _y){
    resize(_w, _h);
}


_Polygon::_Polygon(int _x, int _y, int _w, int _h, Color* col):
    Drawable(_x, _y, col){
    resize(_w, _h);
}

_Polygon::_Polygon(int _x, int _y, int _w, int _h, Color** col):
    Drawable(_x, _y, col){
    resize(_w, _h);
}

void _Polygon::resize(int w, int h){
    width  = w;
    height = h;
}

void _Polygon::draw(int mask){
    mask |= GL_POLYGON;
    Drawable::draw(mask, [&](int x, int y){
        // To GLUT's weird coord. system
        y = window_height - y;
        int offset_x = width  * anchor;
        int offset_y = height * anchor;
        int lx = x - offset_x, rx = x + width - offset_x;
        int uy = y - offset_y, dy = y + height - offset_y;
        glVertex2i(lx, uy);
        glVertex2i(rx, uy);
        glVertex2i(rx, dy);
        glVertex2i(lx, dy);
    });
}
