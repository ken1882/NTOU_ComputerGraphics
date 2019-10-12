#include "main.h"

Circle::Circle(int _x, int _y, int _r):
    Drawable(_x, _y){
    set_radius(_r);
}

Circle::Circle(int _x, int _y, int _r, Color* col):
    Drawable(_x, _y, col){
    set_radius(_r);
}

Circle::Circle(int _x, int _y, int _r, Color** col):
    Drawable(_x, _y, col){
    set_radius(_r);
}

void Circle::set_radius(int _r){
    radius = _r;
    circle_pts = radius * 16;
    angle_delta = 2 * PI / circle_pts;
}

void Circle::draw(int mask){
    mask |= GL_POLYGON;
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, window_height - y, 0.0f);
    Drawable::draw(mask, [&](int x, int y){
        y = window_height - y;
        glVertex2d(radius * cos(0.0), radius * sin(0.0));
        double cur_angle = 0.0;
        for(int i=0;i<circle_pts;++i){
            glVertex2d(radius * cos(cur_angle), radius * sin(cur_angle));
            cur_angle += angle_delta;
        }
    });
    glPopMatrix();
}
