#include "main.h"

namespace EventManager{
    int event_id = -1;

    void envoke_menu_event(int eid){
        event_id = eid;
        string placeholder = "";
        switch(eid){
        case MW_BCOLOR:
            placeholder = Vocab::COLOR_INPUT_PLACEHOLDER;
            Input::process_input(placeholder.c_str());
            break;
        case MW_BSIZE:
            SetWindowLongPtr(edit_input_handler, GWL_STYLE, WSSizeEdit);
            placeholder = Vocab::SIZE_INPUT_PLACEHOLDER;
            Input::process_input(placeholder.c_str());
            break;
        case MW_PENCIL:
            Cursor::setMode(Cursor::PENMODE_DRAW);
            break;
        case MW_ERASER:
            Cursor::setMode(Cursor::PENMODE_ERASER);
            break;
        case MW_PPOLY:
            Cursor::setPenType(Cursor::PENTYPE_POLY);
            break;
        case MW_PCIRCLE:
            Cursor::setPenType(Cursor::PENTYPE_CIRCLE);
            break;
        case MW_CLEAR:
            App::clear_all(false);
            break;
        }
    }

    void envoke_input_event(){
        switch(event_id){
        case MW_BCOLOR:
            return change_pencil_color();
        case MW_BSIZE:
            return change_pencil_size();
        }
    }

    void change_pencil_color(){
        string col_str = Input::retrieve_input();
        std::stringstream ss(col_str);
        std::vector<int> rgb;
        int n;
        while(ss >> n){
            if(n < 0){n = 0;}
            else if(n > 0xff){n = 0xff;}
            rgb.push_back(n);
        }
        if(rgb.size() > 0){
            Cursor::pencil_color -> change(rgb[0], rgb[1], rgb[2]);
        }
    }

    void change_pencil_size(){
        string sz_str = Input::retrieve_input();
        std::stringstream ss(sz_str);
        int n;
        if(ss >> n){
            if(n < 1){n = 1;}
            else if(n > 128){n = 128;}
        }
        Cursor::change_pencil_size(n);
    }
}
