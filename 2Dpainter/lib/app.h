#include "main.h"

#ifndef INCLUDE_APP
#define INCLUDE_APP

namespace App{
    extern bool is_fullscreen;
    void update();
    void clear_all(bool prompt=false);
    void refresh();
    void on_display();
    void on_reshape(int, int);
    void on_keyboard(unsigned char, int, int);
    void on_mouse(int, int, int, int);
    void on_drag(int, int);
    void resize_window(int, int);
    void reload_canvas(int,int);
    void process_control_commands(unsigned char,int,int);
    void process_menu_commands(unsigned char,int, int);

    void update_input_window();
}

#endif // INCLUDE_APP
