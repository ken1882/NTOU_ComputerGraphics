#include "main.h"

#ifndef INCLUDE_VOCAB
#define INCLUDE_VOCAB

typedef const char* CSTR;

namespace Vocab{
    static CSTR SAVE = "Save";
    static CSTR LOAD = "Load";
    static CSTR LINE = "Line";
    static CSTR SQUARE = "Square";
    static CSTR RECT = "Rectangle";
    static CSTR POLYGON = "Polygon";
    static CSTR CIRCLE = "Circle";
    static CSTR CURVE = "Curve";
    static CSTR COLOR = "Color";
    static CSTR SIZE = "Size";
    static CSTR QUIT_CONFIRM = "Do you really want to quit?";
    static CSTR CLEAR_CONFIRM = "Do you really want to clear all content?";
    static CSTR BRUSH = "Brush";
    static CSTR PENCIL = "Pencil";
    static CSTR ERASER = "Eraser";
    static CSTR TYPE = "Type";
    static CSTR CLEAR = "Clear";
    static CSTR FILE = "File";
    static CSTR ADDOBJ = "Add object";

    static CSTR COLOR_INPUT_PLACEHOLDER = "Enter the RGB value here.\r\n"
                                          "EX: \"255 255 255\" for white (no quotes)";

    static CSTR SIZE_INPUT_PLACEHOLDER = "Enter the brush size here (1~128)";
    static CSTR SAVING_MSG = "Saving image, please wait...";
    static CSTR SAVE_OK_MSG = "Save completed!";
    static CSTR SAVE_FAIL_MSG = "Save failed...please retry later";

    static CSTR POLY_INPUT_PLACEHOLDER = "Enter the sides you want to draw here (3~8)";
    static CSTR BAD_IMG = "Malformed Image!";
}
#endif // INCLUDE_VOCAB
