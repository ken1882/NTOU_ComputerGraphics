#pragma once
#ifndef INCLUDE_MAIN
#define INCLUDE_MAIN

#include <windows.h>
#include <shellapi.h>

#define EM_SETCUEBANNER 0x1501

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <initializer_list>
#include <memory>
#include <fstream>
#include <deque>
#include <functional>
#include <sstream>
#include <cmath>

#include <gl/freeglut.h>

#define cimg_use_cpp11 1
#define cimg_use_jpeg 1
#define cimg_use_png 1
#include "CImg.h"

#define WindowWidth  800 // Default Window Width
#define WindowHeight 800 // Default Window Height

using std::cout;
using std::unique_ptr;
using std::shared_ptr;
using std::string;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern const char* WINDOW_TITLE;
extern HWND APP_HANDLE;
extern HDC APP_DC;
extern LONG ORI_WINSTYLE;  // Original WS before full-screen
extern RECT ori_winrect;   // Original Window Rect before full-screen
extern const int WIN_CLOSE_RECT[2];
extern int window_width, window_height;
extern std::vector<GLuint> canvas; // Current DC

extern bool DEBUG_MODE;
extern int MAX_TRACE;

bool is_window_closing(MSG&);
bool is_mouse_closing(MSG&);
bool is_keybord_closing(MSG&);
bool is_in_input();

bool basic_update();
void force_update(int);
void main_update();
void init_menu(HINSTANCE);

extern int menu_main;
extern int menu_brush;
extern int menu_file;
extern int menu_btype;
extern int menu_polygon;

static const int MW_BCOLOR  = 1;
static const int MW_BSIZE   = 2;
static const int MW_PENCIL  = 3;
static const int MW_ERASER  = 4;
static const int MW_PPOLY   = 5;
static const int MW_PCIRCLE = 6;
static const int MW_CLEAR   = 7;
static const int MW_SAVE    = 8;
static const int MW_LOAD    = 9;
static const int MW_OLINE   = 10;
static const int MW_OPOLY   = 11;
static const int MW_OCURVE  = 12;
static const int MW_TEXT    = 13;
static const int MW_MPOLY_FILL = 14;
static const int MW_MPOLY_NOFILL = 15;

extern HWND edit_input_handler;

static const int WSBaseEdit  = WS_CHILD | WS_BORDER | ES_MULTILINE;
static const int WSSizeEdit  = ES_NUMBER;

static const int WINPUT_WIDTH   = 280;
static const int WINPUT_HEIGHT  = 38;

static const double PI = acos(-1);
static const double GL_MAX_LINE_WIDTH = 10.0;

#include "vocab.h"
#include "input.h"
#include "util.h"
#include "pos.h"
#include "file_util.h"
#include "color.h"
#include "drawable.h"
#include "polygon.h"
#include "line.h"
#include "circle.h"

#include "app.h"
#include "cursor.h"
#include "record.h"
#include "tracer.h"
#include "event_manager.h"

//--------------------

#endif // INCLUDE_MAIN
