#include "main.h"

namespace EventManager{
    int event_id = -1;

    void envoke_menu_event(int eid){
        event_id = eid;
        switch(eid){
        case MW_CLEAR:
            App::clear_all();
            break;
        case MW_UNDO:
            Tracer::restore_last();
            break;
        case MW_REDO:
            Tracer::restore_next();
            break;
        case MW_BCOLOR:
        case MW_BSIZE:
        case MW_PENCIL:
        case MW_ERASER:
        case MW_PPOLY:
        case MW_PCIRCLE:
            return envoke_brush_event();
        case MW_OLINE:
        case MW_OCURVE:
        case MW_OPOLY:
        case MW_TEXT:
        case MW_MPOLY_FILL:
        case MW_MPOLY_NOFILL:
            return envoke_object_event();
        case MW_SAVE:
        case MW_LOAD:
            return envoke_file_event();
        }
    }

    void envoke_input_event(){
        switch(event_id){
        case MW_BCOLOR:
            return change_pencil_color();
        case MW_BSIZE:
            return change_pencil_size();
        case MW_OPOLY:
            return process_polygon_drawing();
        case MW_TEXT:
            return process_text_insert();
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

    void process_polygon_drawing(){
        string sz_str = Input::retrieve_input();
        std::stringstream ss(sz_str);
        int n;
        if(ss >> n){
            if(n < 3){n = 3;}
            else if(n > 8){n = 8;}
        }
        Cursor::process_polygon_drawing(n);
    }

    void envoke_brush_event(){
        string placeholder = "";
        switch(event_id){
        case MW_BCOLOR:
            placeholder = Vocab::COLOR_INPUT_PLACEHOLDER;
            Input::process_input(placeholder.c_str());
            break;
        case MW_BSIZE:
            placeholder = Vocab::SIZE_INPUT_PLACEHOLDER;
            Input::process_input(placeholder.c_str(), WSSizeEdit);
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
        }
    }

    void envoke_file_event(){
        switch(event_id){
        case MW_SAVE:
            Util::save_image();
            break;
        case MW_LOAD:
            Util::load_image();
            break;
        }
    }

    void envoke_object_event(){
        string placeholder = "";
        switch(event_id){
        case MW_OLINE:
            Cursor::setMode(Cursor::PENMODE_OBJ_LINE);
            break;
        case MW_OPOLY:
            placeholder = Vocab::POLY_INPUT_PLACEHOLDER;
            Input::process_input(placeholder.c_str(), WSSizeEdit);
            break;
        case MW_TEXT:
            placeholder = Vocab::TXT_INPUT_PLACEHOLDER;
            Input::process_input(placeholder.c_str());
            break;
        case MW_MPOLY_FILL:
            Cursor::poly_filled = true;
            break;
        case MW_MPOLY_NOFILL:
            Cursor::poly_filled = false;
            break;
        }
    }

    void process_text_insert(){
        float r = Cursor::pencil_color -> r;
        float g = Cursor::pencil_color -> g;
        float b = Cursor::pencil_color -> b;
        int mx  = Cursor::menu_x;
        int my  = Cursor::menu_y;
        glColor3f(r, g, b);
        glRasterPos2i(mx, window_height - my);
        string in_str = Input::retrieve_input();
        in_str = Util::str_chomp(in_str);
        auto font = GLUT_BITMAP_9_BY_15;
        int len = in_str.length();
        for(int i=0;i<len;++i){
            glutBitmapCharacter(font, in_str[i]);
        }
        App::refresh();
        Util::set_trace_point(0);
    }
}
