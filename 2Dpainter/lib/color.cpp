#include "main.h"

Color* DefaultColor = new Color(1, 1, 1);

Color::Color(double _r, double _g, double _b, double _a){
    change(_r, _g, _b, _a);
}

Color::Color(Color* col){
    change(col -> r, col -> g, col -> b, col -> a);
}

GLuint Color::to_uint(){
    int base = 0;
    int alpha = a * 0xff;
    int red   = r * 0xff;
    int green = g * 0xff;
    int blue  = b * 0xff;
    base |= alpha << (6 * 4);
    base |= blue  << (4 * 4);
    base |= green << (2 * 4);
    base |= red;
    return base;
}

void Color::change(double _r, double _g, double _b, double _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void Color::change(int _r, int _g, int _b, int _a){
    change(_r / 255.0, _g / 255.0, _b / 255.0, _a / 255.0);
}
