#include "main.h"

namespace App{
    bool is_fullscreen = false;

    void update(){
        if(Input::is_trigger(VK_F11)){
            Util::to_fullscreen(is_fullscreen);
            is_fullscreen ^= 1;
        }
        if(!is_fullscreen){Util::update_window_rect();}

        if(is_in_input()){
            update_input_window();
        }
    }

    void clear_all(bool prompt){
        if(prompt){
            if(MessageBox(APP_HANDLE, Vocab::CLEAR_CONFIRM, WINDOW_TITLE, MB_OKCANCEL) != IDOK){
                return ;
            }
        }
        Cursor::abort_polygon_drawing();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        refresh();
        Util::set_trace_point(Record::ACTION_PENCIL);
    }

    void refresh(){
        glFlush();
        glutPostRedisplay();
    }

    void resize_window(int w, int h){
        glViewport( 0, 0, w, h);
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
    }

    void on_display(){
        std::cout << "display\n";
    }

    void on_reshape(int w, int h){
        printf("reshape: %d %d\n", w, h);
        window_width  = w;
        window_height = h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, (double) w, 0.0, (double) h);
        glViewport(0, 0, w, h);
        glMatrixMode(GL_MODELVIEW);
        reload_canvas(w, h);
    }

    void on_mouse(int vk, int stat, int x, int y){
        printf("mouse: %d %d %d %d\n", vk, stat, x, y);
        if(vk == GLUT_LEFT_BUTTON){
            Cursor::on_click(vk, stat, x, y);
        }
    }

    void on_keyboard(unsigned char vk, int x, int y){
        printf("keyboard: %d %d %d\n", vk, x, y);

        if(Input::is_press(VK_CONTROL)){
            process_control_commands(vk, x, y);
        }
        else if(Input::is_press(VK_MENU)){
            process_menu_commands(vk, x, y);
        }
        else if(Input::is_trigger(VK_DELETE)){
            clear_all();
        }
        else if(Input::is_trigger(Input::keymap::VK_T)){
            // reserved
        }
    }

    void on_drag(int mx, int my){
        if(!Cursor::is_moved()){return;}
        if(Input::is_press(Input::keymap::VK_MOUSE1)){
            Cursor::on_drag(mx, my);
        }
    }

    void process_control_commands(unsigned char _, int x, int y){
        if(Input::is_trigger(Input::keymap::VK_S)){
            cout << "Saving image\n";
            Util::save_image();
        }
        else if(Input::is_trigger(Input::keymap::VK_Z)){
            cout << "Undo\n";
            cout << Tracer::restore_last() << '\n';
        }
        else if(Input::is_trigger(Input::keymap::VK_Y)){
            cout << "Redo\n";
            cout << Tracer::restore_next() << '\n';
        }
    }

    void process_menu_commands(unsigned char vk, int x, int y){

    }

    void reload_canvas(int nw, int nh){
        canvas.resize(nw * nh);
        Tracer::reload_current_record();
    }

    void update_input_window(){
        RECT _rect;
        GetWindowRect(edit_input_handler, &_rect);
        if(Input::is_trigger(Input::keymap::VK_MOUSE1) &&
           Cursor::is_in_rect(_rect, true)){
            cout << "Edit focus\n";
            SetWindowText(edit_input_handler, "");
        }
        else if(Input::is_trigger(VK_RETURN)){
            EventManager::envoke_input_event();
        }
    }
}
