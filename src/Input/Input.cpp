#include "Input.h"

std::vector<Uint8> Input::previousKeyboardState;

void Input::initialize()
{
    int numKeys;
    SDL_GetKeyboardState(&numKeys);
    previousKeyboardState.resize(numKeys);
}

bool Input::GetKey(const SDL_Keycode key)
{
    auto keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_GetScancodeFromKey(key)] && previousKeyboardState[SDL_GetScancodeFromKey(key)])
        return true;
    return false;
}

bool Input::GetKeyDown(const SDL_Keycode key)
{
    auto keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_GetScancodeFromKey(key)] && !previousKeyboardState[SDL_GetScancodeFromKey(key)])
        return true;
    return false;
}

bool Input::GetKeyUp(const SDL_Keycode key)
{
    auto keyboardState = SDL_GetKeyboardState(nullptr);
    if (!keyboardState[SDL_GetScancodeFromKey(key)] && previousKeyboardState[SDL_GetScancodeFromKey(key)])
        return true;
    return false;
}

void Input::update()
{
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    std::memcpy(previousKeyboardState.data(), keyboardState, previousKeyboardState.size());
}
