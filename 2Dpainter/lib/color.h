#include "main.h"

#ifndef INCLUDE_COLOR
#define INCLUDE_COLOR

struct Color{
    double r, g, b, a;
    Color(double,double,double,double _a=1.0);
    Color(Color*);
    GLuint to_uint();

    void change(double,double,double,double _a=1.0);
    void change(int,int,int,int a=0xff);
};

extern Color* DefaultColor;
#endif
