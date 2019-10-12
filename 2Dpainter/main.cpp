#include "lib/main.h"

// application title
const char* WINDOW_TITLE = "2D Painter";

// Width & Height of "X" button
const int WIN_CLOSE_RECT[] = {48, 32};

int SCREEN_WIDTH = 1, SCREEN_HEIGHT = 1;

HWND APP_HANDLE;    // GLUT window handle
HDC APP_DC;         // GLUT canvas device context
LONG ORI_WINSTYLE;  // Window Style before full-screen enabled
RECT ori_winrect;   // Window Rect before full-screen enabled
bool DEBUG_MODE;    // Debug mode flag
int MAX_TRACE;      // Max undo trace backs


int menu_main;
int menu_brush;
int menu_file;
int menu_btype;
HWND edit_input_handler;

std::vector<GLuint> canvas;  // canvas information holder

int window_width = 1, window_height = 1; // window width & height

void terminate(); // window close clean ups


// define cout<< for vector
template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const ve){
    os << "[";
    int len = ve.size();
    if(len > 0){os << ve[0];}
    for(int i=1;i<len;++i){os << ", " << ve[i];}
    return os << "]";
}

// initialize glut
void init_glut(int argc, char* argv[]){
    glutInit(&argc, argv);
    SCREEN_WIDTH  = glutGet(GLUT_SCREEN_WIDTH);
    SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WindowWidth, WindowHeight);
    int wx = (int)Util::centralize(SCREEN_WIDTH, WindowWidth);
    int wy = (int)Util::centralize(SCREEN_HEIGHT, WindowHeight);
    glutInitWindowPosition(wx, wy);
}

// program initialize
void init(int argc, char* argv[]){
    string path = (FileUtil::pwd() + "\\config.ini");
    DEBUG_MODE = GetPrivateProfileInt("SYSTEM", "Debug", 0, path.c_str());
    MAX_TRACE  = GetPrivateProfileInt("SYSTEM", "MaxTrace", 0, path.c_str());

    printf("Debug mode: %d\n", DEBUG_MODE);
    printf("Max traces: %d\n", MAX_TRACE);

    init_glut(argc, argv);
    glutCreateWindow(WINDOW_TITLE); // create
    APP_HANDLE = FindWindow(NULL, WINDOW_TITLE);
    ORI_WINSTYLE = GetWindowLongPtr(APP_HANDLE, GWL_STYLE);

    GetWindowRect(APP_HANDLE, &ori_winrect);

    Cursor::init();
    Input::init();

    auto ve = Util::get_screen_size();
    cout << "Screen Resolution: " << ve << '\n';
}

// basic handle updates
void basic_update(){
    Input::update();
    Cursor::update();
}

// main window updates
void main_update(){
    glutMainLoopEvent();
    App::update();
}


void register_glut_callbacks(){
    glutDisplayFunc(App::on_display);
    glutReshapeFunc(App::on_reshape);
    glutMouseFunc(App::on_mouse);
    glutKeyboardFunc(App::on_keyboard);
    glutMotionFunc(App::on_drag);
}


// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   LPSTR lpCmdLine, int nShowCmd){

    // retrieve command line arguments
    int argc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    char** argv = new char*[argc];
    for(int i=0;i<argc;++i){
        argv[i] = new char [0xff];
        memset(argv[i], 0, 0xff);
        wcstombs(argv[i], wargv[i], 0xff);
    }

    init(argc, argv);
    delete argv;
    if(!DEBUG_MODE){FreeConsole();}

    register_glut_callbacks();
    cout << "Debug Mode: " << DEBUG_MODE << '\n';

    APP_DC = GetDC(APP_HANDLE);
    Util::init();
    init_menu(hInstance);
    App::clear_all(true);

    // main message loop
    try{
        MSG message;
        while(GetMessage(&message, NULL, 0, 0)){
            Sleep(0);
            basic_update();
            TranslateMessage(&message);
            if(!is_window_closing(message)){
                DispatchMessage(&message);
            }
            else{
                if(MessageBox(APP_HANDLE, Vocab::QUIT_CONFIRM, WINDOW_TITLE, MB_OKCANCEL) == IDOK){
                    PostQuitMessage(0);
                }
            }
            main_update();
        }
    }
    catch(int e){
        printf("An error occurred! (code: %d)\n", e);
    };
    terminate();
    return 0;
}

bool is_window_closing(MSG& message){
    return is_mouse_closing(message) || is_keybord_closing(message);
}

// check mouse is at window "X" area
bool is_mouse_closing(MSG& message){
    auto msg = message.message;
    POINT cpos; GetCursorPos(&cpos);
    if(msg != WM_NCLBUTTONDOWN && msg != WM_NCLBUTTONUP){return false;}
    if(cpos.x < ori_winrect.right - WIN_CLOSE_RECT[0]){return false;}
    if(cpos.y > ori_winrect.top + WIN_CLOSE_RECT[1]){return false;}
    return true;
}

// check alt + F4
bool is_keybord_closing(MSG& message){
    auto msg = message.message;
    if(!GetKeyState(VK_MENU)){return false;}
    if(msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP){
        if(message.wParam == VK_F4){return true;}
    }
    return false;
}

// clean ups
void terminate(){
    delete DefaultColor;
    Cursor::terminate();
    Tracer::terminate();
}

void topmenu_func(int _){}

void init_menu(HINSTANCE parent_ins){
    int ww = WINPUT_WIDTH, wh = WINPUT_HEIGHT;
    int wx = Util::centralize(window_width, ww);
    int wy = Util::centralize(window_height, wh);
    edit_input_handler = CreateWindowEx(0, "Edit", "",
                                      WSBaseEdit | WS_DISABLED,
                                      wx, wy, ww, wh,
                                      APP_HANDLE, 0, parent_ins,0);

    menu_btype = glutCreateMenu(EventManager::envoke_menu_event);
    glutAddMenuEntry(Vocab::POLYGON, MW_PPOLY);
    glutAddMenuEntry(Vocab::CIRCLE, MW_PCIRCLE);

    menu_brush = glutCreateMenu(EventManager::envoke_menu_event);
    glutAddMenuEntry(Vocab::COLOR, MW_BCOLOR);
    glutAddMenuEntry(Vocab::SIZE, MW_BSIZE);
    glutAddMenuEntry(Vocab::PENCIL, MW_PENCIL);
    glutAddMenuEntry(Vocab::ERASER, MW_ERASER);
    glutAddSubMenu(Vocab::TYPE, menu_btype);

    menu_main = glutCreateMenu(EventManager::envoke_menu_event);
    glutAddMenuEntry(Vocab::CLEAR, MW_CLEAR);
    glutAddSubMenu(Vocab::BRUSH, menu_brush);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

bool is_in_input(){
    return IsWindowVisible(edit_input_handler);
}
