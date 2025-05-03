#pragma once
#include <vector>

#include "SDL_keyboard.h"
#include "SDL_keycode.h"

class Input
{
public:
    static void initialize();
    static bool GetKey(const SDL_Keycode key);
    static bool GetKeyDown(const SDL_Keycode key);
    static bool GetKeyUp(const SDL_Keycode key);
    static void update();


private:
    static std::vector<Uint8> previousKeyboardState;
};
