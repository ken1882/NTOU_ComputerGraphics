#include "main.h"

#ifndef INCLUDE_UTIL
#define INCLUDE_UTIL


template <typename Enumeration>
typename std::underlying_type<Enumeration>::type enum2int(Enumeration const value);

std::ostream& operator<<(std::ostream& os, Input::keymap const& enum_val);
std::ostream& operator<<(std::ostream& os, RECT const);
std::ostream& operator<<(std::ostream& os, std::vector<int> const&);

namespace Util{

    void init();

    template <typename T>
    void get_class(T obj);

    double centralize(double, double);

    void update_window_rect();
    void to_fullscreen(bool);
    std::vector<int> get_screen_size();

    bool get_bit_mask(int mask, int bit);
    bool save_image();
    bool load_image();
    bool save_as_bmp(const char* path, HDC context = NULL, RECT area = {-1, -1, -1, -1});
    string prompt_save_dialog();
    string bmp2png(const char*, const char*);
    string bmp2jpg(const char*, const char*);

    void save_buffer();
    void load_buffer(std::vector<GLuint>,int,int);
    std::vector<unsigned char> int2rgba(int);

    void set_trace_point(int);
    void set_trace_point(int, void* _obj);
    void popup_hint(const char*);
    void hide_hint();

    void resize_window(int,int);
}
#endif // INCLUDE_UTIL
