#include "main.h"

#ifndef INCLUDE_RECORD
#define INCLUDE_RECORD

struct Record{
    static const int TYPE_FRAME = 0;
    static const int TYPE_OBJ = 1;
    static const int ACTION_PENCIL = 0;
    static const int ACTION_ERASER = 1;
    int type, action;
    int buffer_width, buffer_height;
    std::vector<GLuint> buffer;

    Record(int, int);
    Record(int, int, std::vector<GLuint>);

    void restore();
    void restore_frame();
    void restore_object();
    void transform_buffer();

private:
    void init();
};

#endif // INCLUDE_RECORD
