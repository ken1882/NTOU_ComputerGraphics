#include "main.h"

namespace Cursor{
    int x, y;   // cursor position in client area
    int gx, gy; // cursor position on screen

    int last_dx, last_dy; // last cursor position in client area
    int last_gx, last_gy; // last cursor position on screen

    int obj_sx, obj_sy;   // Object starting position
    int menu_x, menu_y;   // GLUT menu position

    Color* pencil_color;
    Color* eraser_color;
    int ori_pen_color[4] = {0};


    _Polygon* pencil_poly;  // pencil polygon object

    Line* pencil_joiner; // Fix the pencil drawing gap
                         // between each frame update

    Circle* pencil_circle; // Circle drawing
    Circle* point_indicator;

    std::vector<POINT> obj_pts; // Object points
    int poly_pts_cnt = -1;      // Object points count
    bool poly_filled = true;

    void init(int sx, int sy){
        pencil_color = new Color(DefaultColor);
        pencil_poly = new _Polygon(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, &pencil_color);
        pencil_poly -> anchor = 0.5;
        pencil_joiner = new Line(0, 0, 0, 0, DEFAULT_WIDTH, &pencil_color);
        eraser_color = new Color(0, 0, 0, 0);

        pencil_circle = new Circle(0, 0, DEFAULT_WIDTH/2, &pencil_color);
        point_indicator = new Circle(0, 0, DEFAULT_WIDTH/2, &pencil_color);

        setPenType(PENTYPE_CIRCLE);
        backup_pencil_color();
        setMode(PENMODE_DRAW);
        setPos(sx, sy);

        obj_sx = -1;
        obj_sy = -1;
    }

    void setPos(int _x, int _y){
        x = _x;
        y = _y;
    }

    void update(){
        POINT pos;
        GetCursorPos(&pos);
        last_gx = gx; last_gy = gy;
        gx = pos.x; gy = pos.y;
        ScreenToClient(APP_HANDLE, &pos);
        x = pos.x; y = pos.y;
        if(obj_sx != -1 && is_moved()){
            update_object_preview();
        }

        if(Input::is_trigger(Input::keymap::VK_MOUSE2)){
            menu_x = x;
            menu_y = y;
        }
    }

    void setPenType(int t){
        pen_type = t;
        int base = 1;
        switch(t){
        case PENTYPE_POLY:
            base = pencil_poly -> width;
            break;
        case PENTYPE_CIRCLE:
            base = pencil_circle -> radius * 2.3;
            break;
        }
        pencil_joiner -> line_width = base;
    }

    void setMode(int m){
        if(obj_pts.size() > 0){
            abort_polygon_drawing();
        }
        mode = m;
        int _r = ori_pen_color[0];
        int _g = ori_pen_color[1];
        int _b = ori_pen_color[2];
        int _a = ori_pen_color[3];
        switch(mode){
        case PENMODE_DRAW:
            pencil_color -> change(_r, _g, _b, _a);
            break;
        case PENMODE_ERASER:
            backup_pencil_color();
            _r = eraser_color -> r * 0xff;
            _g = eraser_color -> g * 0xff;
            _b = eraser_color -> b * 0xff;
            _a = eraser_color -> a * 0xff;
            pencil_color -> change(_r, _g, _b, _a);
            break;
        }
    }

    void on_click(int vk, int stat, int cx, int cy){
        if(is_in_input()){
            Input::abort_input();
            return ;
        }
        setPos(cx, cy);
        if(stat == GLUT_DOWN){
            switch(mode){
            case PENMODE_DRAW:
            case PENMODE_ERASER:
                draw_pencil();
                last_dx = x;
                last_dy = y;
                break;
            case PENMODE_OBJ_LINE:
                set_obj_bpos(x, y);
                break;
            case PENMODE_OBJ_POLY:
                update_polygon_preview();
                break;
            }
        }
        else if(stat == GLUT_UP){
            switch(mode){
            case PENMODE_DRAW:
            case PENMODE_ERASER:
            case PENMODE_OBJ_LINE:
                finalize_object();
                Util::set_trace_point(Record::ACTION_PENCIL);
                break;
            }
        }
    }

    void on_drag(int cx, int cy){
        setPos(cx, cy);
        switch(mode){
        case PENMODE_DRAW:
        case PENMODE_ERASER:
            draw_pencil();
            fix_pencil_gap();
            last_dx = x;
            last_dy = y;
            break;
        }
    }

    int current_mode(){return mode;}

    // pencil draw on canvas
    void draw_pencil(){
        switch(pen_type){
        case PENTYPE_POLY:
            pencil_poly -> setPos(x, y);
            pencil_poly -> draw(DW_FLUSH);
            break;
        case PENTYPE_CIRCLE:
            pencil_circle -> setPos(x, y);
            pencil_circle -> draw(DW_FLUSH);
            break;
        }
    }

    // fill the pencil drag drawing gap
    void fix_pencil_gap(){
        if(pencil_joiner -> line_width <= GL_MAX_LINE_WIDTH){
            pencil_joiner -> setPos(last_dx, last_dy);
            pencil_joiner -> setDest(x, y);
            pencil_joiner -> draw(DW_FLUSH);
            return ;
        }
    }

    // whether mouse is moved
    bool is_moved(){
        return last_gx != gx || last_gy != gy;
    }

    void terminate(){
        delete pencil_color;
        delete eraser_color;
        delete pencil_poly;
        delete pencil_joiner;
        delete pencil_circle;
        delete point_indicator;
    }

    bool is_in_rect(RECT _rect, bool global){
        int cx = global ? gx : x;
        int cy = global ? gy : y;
        if(cy < _rect.top){return false;}
        if(cy > _rect.bottom){return false;}
        if(cx < _rect.left){return false;}
        if(cx > _rect.right){return false;}
        return true;
    }

    void change_pencil_size(int pts){
        pencil_poly -> resize(pts, pts);
        pts /= 2;
        pts = (pts == 0 ? 1 : pts);
        pencil_circle -> set_radius(pts);

        setPenType(pen_type); // apply new point size on joiner
    }

    void backup_pencil_color(){
        ori_pen_color[0] = pencil_color -> r * 0xff;
        ori_pen_color[1] = pencil_color -> g * 0xff;
        ori_pen_color[2] = pencil_color -> b * 0xff;
        ori_pen_color[3] = pencil_color -> a * 0xff;
    }

    void set_obj_bpos(int sx, int sy){
        obj_sx = sx;
        obj_sy = sy;
    }

    void update_object_preview(){
        switch(mode){
        case PENMODE_OBJ_LINE:
            return update_line_preview();
        }
    }

    void update_line_preview(){
        Tracer::reload_current_record();
        pencil_joiner -> setPos(obj_sx, obj_sy);
        pencil_joiner -> setDest(x, y);
        pencil_joiner -> draw(DW_FLUSH);
    }

    void update_polygon_preview(){
        POINT pt;
        pt.x = x; pt.y = y;
        point_indicator -> setPos(x, y);
        point_indicator -> draw(DW_FLUSH);
        obj_pts.push_back(pt);
        if(obj_pts.size() >= poly_pts_cnt){
            finalize_polygon();
        }
    }

    void finalize_object(){
        switch(mode){
        case PENMODE_OBJ_LINE:
            return finalize_line(x, y);
        }
        if(mode == PENMODE_OBJ_POLY && obj_pts.size() >= poly_pts_cnt){
            return finalize_polygon();
        }
    }

    void finalize_line(int fx, int fy){
        Tracer::reload_current_record();
        pencil_joiner -> setPos(obj_sx, obj_sy);
        pencil_joiner -> setDest(fx, fy);
        pencil_joiner -> draw(DW_FLUSH);
        obj_sx = -1;
        obj_sy = -1;
    }

    void process_polygon_drawing(int sides){
        poly_pts_cnt = sides;
        setMode(PENMODE_OBJ_POLY);
    }

    void abort_polygon_drawing(){
        glPolygonMode(GL_FRONT, GL_FILL);
        Tracer::reload_current_record();
        obj_pts.clear();
        App::refresh();
    }

    void finalize_polygon(){
        Tracer::reload_current_record();
        float r = pencil_color -> r;
        float g = pencil_color -> g;
        float b = pencil_color -> b;
        auto pmode = GL_FILL;
        if(!poly_filled){
            pmode = GL_LINE;
            glLineWidth(pencil_joiner -> line_width);
        }
        glColor3f(r, g, b);
        glPolygonMode(GL_FRONT, pmode);
        glBegin(GL_POLYGON);
            for(auto pt:obj_pts){
                glVertex2i(pt.x, window_height - pt.y);
            }
        glEnd();
        Util::set_trace_point(Record::ACTION_PENCIL);;
        abort_polygon_drawing();
    }
}
