#include "main.h"

namespace FileUtil{

    WORD BF_TYPE_BM = 0x4D42;
    WORD BMP_BPP = 32;

    string pwd(){
        char buffer[0xff];
        GetModuleFileName(NULL, buffer, 0xff);
        string::size_type pos = string(buffer).find_last_of("\\/");
        return string(buffer).substr(0, pos);
    }

    // Save DC to bmp file
    bool save_as_bmp(const char* path, HDC context, RECT area){
        if(context == NULL){
            context = APP_DC;
            GetClientRect(APP_HANDLE, &area);
        }
        else if(area.top == -1){
            BITMAP tmp;
            memset(&tmp, 0, sizeof(BITMAP));
            HGDIOBJ tmp_gdi = GetCurrentObject(context, OBJ_BITMAP);
            GetObject(tmp_gdi, sizeof(BITMAP), &tmp);
            DeleteObject(tmp_gdi);
        }

        int bmp_width  = area.right - area.left;
        int bmp_height = area.bottom - area.top;

        printf("Saving bmp (%d x %d)\n", bmp_width, bmp_height);

        BITMAPINFO info;
        BITMAPFILEHEADER header;
        memset(&info, 0, sizeof(info));
        memset(&header, 0, sizeof(header));

        info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        info.bmiHeader.biWidth  = bmp_width;
        info.bmiHeader.biHeight = bmp_height;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = BMP_BPP;
        info.bmiHeader.biCompression = BI_RGB;
        header.bfType = BF_TYPE_BM;
        header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

        char* pixels = NULL;
        HDC tmp_dc = CreateCompatibleDC(context);
        HBITMAP section = CreateDIBSection(context, &info, DIB_RGB_COLORS, (void**)&pixels, 0, 0);
        DeleteObject(SelectObject(tmp_dc, section));
        BitBlt(tmp_dc, 0, 0, bmp_width, bmp_height, context, area.left, area.top, SRCCOPY);
        DeleteDC(tmp_dc);

        std::fstream _file(path, std::ios::out | std::ios::binary);
        if(_file.is_open()){
            _file.write( (char*)&header, sizeof(header) );
            _file.write( (char*)&info.bmiHeader, sizeof(info.bmiHeader) );
            _file.write(pixels, (((BMP_BPP * bmp_width + 31) & ~31) / 8) * bmp_height);
            _file.close();
            DeleteObject(section);
            return true;
        }
        DeleteObject(section);
        return false;
    }

    // Get file save dest. via WinDialog
    string prompt_save_dialog(){
        OPENFILENAME ofn = {0};
        char buffer[MAX_PATH] = {0};
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = APP_HANDLE;
        ofn.lpstrFilter = "PNG Image (*.png)\0*.png\0"
            "JPEG Image (*.jpg;*.jpeg)\0*.jpg;.jpeg\0"
            "Bitmap (24bits) (*.bmp)\0*.bmp\0"
            "All Files (*.*)\0*.*\0";

        ofn.lpstrFile = buffer;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST |
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
        ofn.lpstrDefExt = "bmp";

        GetSaveFileName(&ofn);
        string _ret = ofn.lpstrFile;
        return _ret;
    }

    // convert bmp file to png file
    string bmp2png(const char* bmp_path, const char* png_path){
        cimg_library::CImg<unsigned char> bmp(bmp_path);
        cout << "BMP2PNG: " << bmp_path << " -> " << png_path << '\n';
        bmp.save_png(png_path);
    }

    // convet bmp file to jpeg file
    string bmp2jpg(const char* bmp_path, const char* jpg_path){
        cimg_library::CImg<unsigned char> bmp(bmp_path);
        cout << "BMP2JPG: " << bmp_path << " -> " << jpg_path << '\n';
        bmp.save_jpeg(jpg_path);
    }

}
