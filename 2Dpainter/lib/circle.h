#include "main.h"

#ifndef INCLUDE_CIRCLE
#define INCLUDE_CIRCLE
struct Circle:public Drawable{
    using Drawable::x;
    using Drawable::y;
    using Drawable::color;

    int radius, circle_pts;
    double angle_delta;

    Circle(int,int,int);
    Circle(int,int,int,Color*);
    Circle(int,int,int,Color**);
    void set_radius(int);
    void draw(int);
};
#endif // INCLUDE_CIRCLE
