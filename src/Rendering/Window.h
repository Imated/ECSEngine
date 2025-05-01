#pragma once
#include <string>

#include "glad/glad.h"
#include "SDL.h"
#include "glm/vec2.hpp"
#include <iostream>
#include "Utils/Logger.h"

class Window {
public:

    Window(int width, int height, const std::string& title = "Game");
    ~Window();

    void swapBuffers();
    void pollEvents();
    void clear();
    
    void SetTitle(const std::string&) const;

    static float GetTime();
    SDL_Window* GetWindow() const;
    glm::vec2 GetSize() { return { params.width, params.height }; }
    bool IsOpen() const;

private:

    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    struct WindowParams
    {
        int width;
        int height;
    } params;

    bool isOpen;
};
