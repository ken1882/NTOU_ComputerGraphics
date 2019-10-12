#include "main.h"

Line::Line(int _x, int _y, int _x2, int _y2, int _lw):
    Drawable(_x, _y){
    init(_x2, _y2, _lw);
}

Line::Line(int _x, int _y, int _x2, int _y2, int _lw, Color* col):
    Drawable(_x, _y, col){
    init(_x2, _y2, _lw);
}

Line::Line(int _x, int _y, int _x2, int _y2, int _lw, Color** col):
    Drawable(_x, _y, col){
    init(_x2, _y2, _lw);
}

void Line::init(int _x2, int _y2, int _lw){
    x2 = _x2;
    y2 = _y2;
    line_width = _lw;
}

void Line::setDest(int dx, int dy){
    x2 = dx;
    y2 = dy;
}

void Line::draw(int mask){
    glLineWidth(line_width);
    mask |= GL_LINES;
    Drawable::draw(mask, [&](int _x, int _y){
        _y = window_height - _y;
        int _x2 = x2, _y2 = window_height - y2;
        glVertex2f(_x, _y);
        glVertex2f(_x2, _y2);
    });
}
