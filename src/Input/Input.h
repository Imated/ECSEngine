#pragma once
#include <vector>

#include "SDL_keyboard.h"
#include "SDL_keycode.h"

class Input
{
public:
    Input()
    {
        int numKeys;
        SDL_GetKeyboardState(&numKeys);
        previousKeyboardState.resize(numKeys);
    }
    
    bool GetKey(const SDL_Keycode key)
    {
        auto keyboardState = SDL_GetKeyboardState(nullptr);
        if(keyboardState[SDL_GetScancodeFromKey(key)] && previousKeyboardState[SDL_GetScancodeFromKey(key)])
            return true;
        return false;
    }

    bool GetKeyDown(const SDL_Keycode key)
    {
        auto keyboardState = SDL_GetKeyboardState(nullptr);
        if(keyboardState[SDL_GetScancodeFromKey(key)] && !previousKeyboardState[SDL_GetScancodeFromKey(key)])
            return true;
        return false;
    }

    bool GetKeyUp(const SDL_Keycode key)
    {
        auto keyboardState = SDL_GetKeyboardState(nullptr);
        if(!keyboardState[SDL_GetScancodeFromKey(key)] && previousKeyboardState[SDL_GetScancodeFromKey(key)])
            return true;
        return false;
    }

    void Update()
    {
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        std::memcpy(previousKeyboardState.data(), keyboardState, previousKeyboardState.size());
    }

private:
    std::vector<Uint8> previousKeyboardState;
};
