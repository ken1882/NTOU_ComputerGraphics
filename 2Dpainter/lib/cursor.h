#include "main.h"

#ifndef INCLUDE_CURSOR
#define INCLUDE_CURSOR

namespace Cursor{
    namespace{int mode, pen_type;}  // (private) cursor mode and
                                    //  pen type

    const int PENMODE_NONE = 0;     // selective mode
    const int PENMODE_DRAW = 1;     // drawing mode
    const int PENMODE_ERASER = 2;
    const int PENMODE_OBJ_LINE = 3; // Adding new line
    const int PENMODE_OBJ_POLY = 4;

    // Brush types
    const int PENTYPE_POLY = 0;
    const int PENTYPE_CIRCLE = 1;

    const int DEFAULT_WIDTH  = 4;   // default pencil width
    const int DEFAULT_HEIGHT = 4;   // default pencil height

    extern int x, y, gx, gy;
    extern int last_x, last_y, last_gx, last_gy;
    extern int obj_sx, obj_sy;
    extern int poly_pts_cnt;

    extern Color* pencil_color;
    extern Color* eraser_color;
    extern _Polygon* pencil_poly;
    extern Line* pencil_joiner;

    void init(int sx=0, int sy=0);
    void update();
    void setPos(int, int);
    void setMode(int);
    void setPenType(int);
    bool is_moved();
    int current_mode();
    void on_click(int,int,int,int);
    void on_drag(int,int);
    void draw_pencil();
    void fix_pencil_gap();
    bool is_in_rect(RECT, bool global=false);

    void terminate();
    void change_pencil_size(int);
    void backup_pencil_color();
    void set_obj_bpos(int,int);
    void update_object_preview();
    void update_line_preview();
    void update_polygon_preview();
    void finalize_object();
    void finalize_line(int,int);
    void finalize_polygon();
    void process_polygon_drawing(int);
    void abort_polygon_drawing();
}
#endif // INCLUDE_CURSOR
