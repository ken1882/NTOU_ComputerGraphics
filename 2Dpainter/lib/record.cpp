#include "main.h"

Record::Record(int _type, int _action){
    type   = _type;
    action = _action;
    init();
}

Record::Record(int _type, int _action, std::vector<GLuint> _buffer){
    type   = _type;
    action = _action;
    buffer = _buffer;
    init();
}


void Record::init(){
    buffer_width  = window_width;
    buffer_height = window_height;
}

void Record::restore(){
    switch(type){
    case TYPE_FRAME:
        restore_frame(); break;
    case TYPE_OBJ:
        restore_object(); break;
    }
}

void Record::restore_frame(){
    Util::load_buffer(buffer, buffer_width, buffer_height);
}

void Record::restore_object(){
    // reserved
}

void Record::transform_buffer(){
    // reserved
}
