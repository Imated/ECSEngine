﻿#include "Window.h"

Window::Window(int width, int height, const std::string& title): isOpen(true)
{
    INFO("Initializing...");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ASSERT("Failed to initialize SDL! Aborting...");
        return;
    }
    INFO("Successfully Initialized SDL2.");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window)
    {
        ASSERT("Failed to create SDL Window! Aborting...");
        SDL_Quit();
        return;
    }
    INFO("Successfully Created Window.");

    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        ASSERT("Failed to create OpenGL context. Aborting...");
        return;
    }
    INFO("Successfully Created OpenGL Context.");
    
    SDL_GetWindowSize(window, &width, &height);
    params.width = width;
    params.height = height;
    INFO("Successfully Fetched Window Size of: %d, %d", width, height);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        ASSERT("Failed to initialize GLAD! Aborting...");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
    INFO("Successfully Initialized OpenGL.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, width, height);

    DEBUG("Initialized Successfully.");
}

void Window::Update()
{
    SDL_GL_SwapWindow(window);
}

void Window::UpdateEvents()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            isOpen = false;
            break;
        case SDL_KEYDOWN:
            if(e.key.keysym.sym == SDLK_ESCAPE)
                isOpen = false;
            break;
        case SDL_WINDOWEVENT_RESIZED:
            int width, height;
            SDL_GetWindowSize(window, &width, &height);
            params.width = width;
            params.height = height;
            glViewport(0, 0, width, height);
            break;
        default:
            break;
        }
    }
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

float Window::GetTime()
{
    return static_cast<float>(SDL_GetTicks()) / 1000;
}

void Window::SetTitle(const std::string& title) const
{
    SDL_SetWindowTitle(window, title.c_str());
}

bool Window::IsOpen() const
{
    return isOpen;
}

SDL_Window* Window::GetWindow() const
{
    return window;
}

float Window::GetAspectRatio() const
{
    return static_cast<float>(params.width) / static_cast<float>(params.height);
}