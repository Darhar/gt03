#include "common.h"
#include "display.h"
#include "screen.h"

#ifndef _GAME_TIGER_KEYBOARD_H
#define _GAME_TIGER_KEYBOARD_H

#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_E 4
#define KEY_F 5
#define KEY_COUNT 6
// 26,27 are analog for joystick
class KeyBoard
{
private:
    const uint8_t pinId[KEY_COUNT] = {7, 6, 3, 4, 28,14};

    bool prevKeyState[KEY_COUNT];
public:
    KeyBoard();
    ~KeyBoard();

    void checkKeyState(Screen *screen);
};

#endif