#include "main.h"

Drawable::Drawable(int _x, int _y):POS(_x, _y){
    color = new Color(DefaultColor);
    anchor = 0;
}

Drawable::Drawable(int _x, int _y, Color* col):POS(_x, _y){
    color = col;
    anchor = 0;
}

Drawable::Drawable(int _x, int _y, Color** col):POS(_x, _y){
    color = *col;
    anchor = 0;
}

Drawable::~Drawable(){
    delete color;
}
