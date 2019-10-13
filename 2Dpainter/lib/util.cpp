#include "main.h"

template <typename Enumeration>
auto enum2int(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

// define cout<< for keymap (enum class)
std::ostream& operator<<(std::ostream& os, Input::keymap const enum_val){
     return os << enum2int(enum_val);
}

// define cout<< for rect
std::ostream& operator<<(std::ostream& os, RECT const rect){
    os << '[';
    os << rect.left << ", " << rect.top << ", " << rect.right << ", " << rect.bottom << "]";
    return os;
}

// define cout<< for vector<int>
std::ostream& operator<<(std::ostream& os, std::vector<int> const& vec){
    os << '[';
    int len = vec.size();
    if(len){os << vec[0];}
    for(int i=1;i<len;++i){
        os << ", " << vec[i];
    }
    os << ']';
    return os;
}

namespace Util{

    void init(){
        main_update();
    }


    template <typename T>
    void get_class(T obj){
        cout << __PRETTY_FUNCTION__ << '\n';
    }

    double centralize(double parent, double child){
        return (parent - child) / 2;
    }

    void update_window_rect(){
        GetWindowRect(APP_HANDLE, &ori_winrect);
    }

    void to_fullscreen(bool reversed){
        LONG new_style = ORI_WINSTYLE;
        auto rect = ori_winrect;
        auto width = rect.right - rect.left;
        auto height = rect.bottom - rect.top;

        int wx = 0, wy = 0;
        if(!reversed){
            //new_style &= ~(WS_CAPTION |WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
            //new_style &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);

            width  = SCREEN_WIDTH;
            height = SCREEN_HEIGHT;
        }
        else{
            wx = ori_winrect.left; wy = ori_winrect.top;
        }
        ShowWindow(APP_HANDLE, SW_HIDE);
        SetWindowLongPtr(APP_HANDLE, GWL_STYLE, new_style);
        ShowWindow(APP_HANDLE, SW_SHOWDEFAULT);
        SetWindowPos(APP_HANDLE, NULL, wx, wy, width, height, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
        // glutPostRedisplay();
    }

    std::vector<int> get_screen_size(){
        return std::vector<int>({SCREEN_WIDTH, SCREEN_HEIGHT});
    }

    bool get_bit_mask(int mask, int bit){
        return (mask >> bit) & 1;
    }

    bool save_image(){
        string full_path = FileUtil::prompt_save_dialog();
        popup_hint(Vocab::SAVING_MSG);
        Sleep(1);
        int len = full_path.length();
        if(len > 0){
            string img_type = "", base_path = "";
            int type_pos = full_path.find_last_of('.');
            for(int i=0;i<len;++i){
                if(i < type_pos){base_path += full_path[i];}
                else{img_type += full_path[i];}
            }

            string dummy_path = "./.tmp.bmp";
            string dest_path  = base_path + img_type;
            if(img_type == ".png"){
                FileUtil::save_as_bmp(dummy_path.c_str());
                FileUtil::bmp2png(dummy_path.c_str(), dest_path.c_str());
                remove(dummy_path.c_str());
            }
            else if(img_type == ".jpg" || img_type == ".jpeg"){
                FileUtil::save_as_bmp(dummy_path.c_str());
                FileUtil::bmp2jpg(dummy_path.c_str(), dest_path.c_str());
                remove(dummy_path.c_str());
            }
            else{
                FileUtil::save_as_bmp(full_path.c_str());
            }
            hide_hint();
            MessageBox(APP_HANDLE, Vocab::SAVE_OK_MSG, WINDOW_TITLE, MB_OK);
            return true;
        }
        hide_hint();
        MessageBox(APP_HANDLE, Vocab::SAVE_FAIL_MSG, WINDOW_TITLE, MB_OK);
        return false;
    }

    void save_buffer(){
        printf("Save buffer (%d x %d)\n", window_width, window_height);
        glReadPixels(0, 0, window_width, window_height,
                     GL_RGBA, GL_UNSIGNED_BYTE, canvas.data());

        for(int i=0;i<window_height;++i){
            for(int j=0;j<window_width;++j){
                int pos = i * window_width + j;
                if(canvas[pos] & 0x00ffffff == 0){
                    canvas[pos] = 0;
                }
                else{
                    canvas[pos] &= 0x00ffffff;
                    canvas[pos] &= 0x7fffffff;
                }
            }
        }
        cout << "Save complete\n";
    }

    void load_buffer(std::vector<GLuint> _buffer, int bwidth, int bheight){
        printf("Load buffer (%d x %d)\n", bwidth, bheight);

        std::vector<GLuint> buffer(window_width * window_height, 0);
        int lwidth  = std::min(bwidth, window_width);
        int lheight = std::min(bheight, window_height);
        for(int i=0;i<lheight;++i){
            for(int j=0;j<lwidth;++j){
                int old_pos = (bheight - 1 - i) * bwidth + j;
                int new_pos = (window_height - 1 - i) * window_width + j;
                buffer[new_pos] = _buffer[old_pos];
            }
        }

        glRasterPos2i(0, 0);
        glDrawPixels(window_width, window_height,
                     GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());
        glFlush();
        cout << "Load complete\n";
    }

    std::vector<unsigned char> int2rgba(int bytes){
        std::vector<unsigned char> ret({0,0,0,0});
        ret[3] = (bytes & 0xff000000) >> 6 * 4;
        ret[2] = (bytes & 0x00ff0000) >> 4 * 4;
        ret[1] = (bytes & 0x0000ff00) >> 2 * 4;
        ret[0] = (bytes & 0x000000ff);
        return ret;
    }

    void set_trace_point(int _act){
        cout << "New trace point\n";
        int tp_idx = Tracer::push(Tracer::record_frame(_act));
        cout << "Trace point " << tp_idx << " saved\n";
    }

    bool load_image(){
        cout << "Load image...\n";
    }

    void popup_hint(const char* msg){
        force_update(3);
        MessageBox(0, msg, WINDOW_TITLE, MB_OK);
        force_update(3);
    }

    void hide_hint(){

    }
}
