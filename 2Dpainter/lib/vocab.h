#include "main.h"

#ifndef INCLUDE_VOCAB
#define INCLUDE_VOCAB

typedef const char* CSTR;

namespace Vocab{
    static CSTR SAVE = "Save";
    static CSTR LOAD = "Load";
    static CSTR LINE = "Line";
    static CSTR RECT = "Rectangle";
    static CSTR POLYGON = "Polygon";
    static CSTR CIRCLE = "Circle";
    static CSTR COLOR = "Color";
    static CSTR SIZE = "Size";
    static CSTR QUIT_CONFIRM = "Do you really want to quit?";
    static CSTR CLEAR_CONFIRM = "Do you really want to clear all content?";
    static CSTR BRUSH = "Brush";
    static CSTR PENCIL = "Pencil";
    static CSTR ERASER = "Eraser";
    static CSTR TYPE = "Type";
    static CSTR CLEAR = "Clear";

    static CSTR COLOR_INPUT_PLACEHOLDER = "Enter the RGB value here.\r\n"
                                          "EX: \"255 255 255\" for white (no quotes)";

    static CSTR SIZE_INPUT_PLACEHOLDER = "Enter the brush size here (1~128)";
}
#endif // INCLUDE_VOCAB
