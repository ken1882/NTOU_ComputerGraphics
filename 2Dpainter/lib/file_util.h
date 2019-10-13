#include "main.h"

#ifndef INCLUDE_FILEUTIL
#define INCLUDE_FILEUTIL

namespace FileUtil{
    string pwd();
    bool save_as_bmp(const char* path, HDC context = NULL, RECT area = {-1, -1, -1, -1});
    string prompt_save_dialog(bool load=false);
    string bmp2png(const char*, const char*);
    string bmp2jpg(const char*, const char*);
}

#endif // INCLUDE_FILEUTIL
