#include "main.h"

namespace Input{
    int keystat[0xff] = {0};

    void init(){
        memset(keystat, 0, sizeof(keystat));
    }

    void update(){
        for(int i=0;i<0xff;++i){
            if(GetAsyncKeyState(i) & 0x8000){
                keystat[i] += 1;
            }
            else{ keystat[i] = 0; }
        }
    }

    bool is_trigger(unsigned char vk){
        return keystat[vk] == 1;
    }

    bool is_press(unsigned char vk){
        return keystat[vk] > 0;
    }

    int is_repeat(unsigned char vk){
        return keystat[vk];
    }

    bool is_trigger(keymap vk){return is_trigger((unsigned char)vk);}
    bool is_press(keymap vk){return is_press((unsigned char)vk);}
    int is_repeat(keymap vk){return is_repeat((unsigned char)vk);}

    void process_input(const char* placeholder){
        EnableWindow(edit_input_handler, 1);
        if(placeholder && placeholder != ""){
            SetWindowText(edit_input_handler, placeholder);
        }
        ShowWindow(edit_input_handler, 1);
        SetFocus(APP_HANDLE);
        glFlush();
        glutPostRedisplay();
    }

    void abort_input(){
        EnableWindow(edit_input_handler, 0);
        SetFocus(APP_HANDLE);
        ShowWindow(edit_input_handler, 0);
        SetWindowLongPtr(edit_input_handler, GWL_STYLE, WSBaseEdit);
        glFlush();
        glutPostRedisplay();
    }

    string retrieve_input(){
        if(is_in_input()){abort_input();}
        char buffer[0xff] = {0};
        GetWindowText(edit_input_handler, buffer, 0xff);
        string ret = buffer;
        return ret;
    }
}
