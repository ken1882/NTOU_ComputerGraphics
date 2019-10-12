#include "main.h"

#ifndef INCLUDE_INPUT
#define INCLUDE_INPUT

namespace Input{
    extern int keystat[0xff];
    enum class keymap{
        VK_MOUSE1 = 1,
        VK_MOUSE2 = 2,
        VK_MOUSE3 = 4,
        VK_0 =  48,
        VK_1 =  49,
        VK_2 =  50,
        VK_3 =  51,
        VK_4 =  52,
        VK_5 =  53,
        VK_6 =  54,
        VK_7 =  55,
        VK_8 =  56,
        VK_9 =  57,
        VK_A =  65,
        VK_B =  66,
        VK_C =  67,
        VK_D =  68,
        VK_E =  69,
        VK_F =  70,
        VK_G =  71,
        VK_H =  72,
        VK_I =  73,
        VK_J =  74,
        VK_K =  75,
        VK_L =  76,
        VK_M =  77,
        VK_N =  78,
        VK_O =  79,
        VK_P =  80,
        VK_Q =  81,
        VK_R =  82,
        VK_S =  83,
        VK_T =  84,
        VK_U =  85,
        VK_V =  86,
        VK_W =  87,
        VK_X =  88,
        VK_Y =  89,
        VK_Z =  90,
    };

    void init();
    void update();

    bool is_trigger(unsigned char);
    bool is_press(unsigned char);
    int is_repeat(unsigned char);

    bool is_trigger(keymap);
    bool is_press(keymap);
    int is_repeat(keymap);

    void process_input(const char* placeholder="");
    void abort_input();
    string retrieve_input();
}
#endif // INCLUDE_INPUT
