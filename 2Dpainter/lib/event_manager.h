#include "main.h"

#ifndef INCLUDE_EVENTMANAGER
#define INCLUDE_EVENTMANAGER

namespace EventManager{
    void envoke_menu_event(int);
    void envoke_input_event();
    void envoke_brush_event();
    void envoke_file_event();
    void envoke_object_event();
    void change_pencil_color();
    void change_pencil_size();
    void process_polygon_drawing();
}

#endif // INCLUDE_EVENTMANAGER
