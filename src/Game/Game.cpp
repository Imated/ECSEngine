#include "Game.h"

#include "Constants.h"
#include "Components/Entity.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Rendering/Window.h"

std::unique_ptr<Window> Game::window;
std::unique_ptr<Input> Game::input;
std::unique_ptr<Scene> Game::scene;

Game::Game(Window* wnd)
{
    window = std::make_unique<Window>(*wnd);
    input = std::make_unique<Input>();
    scene = std::make_unique<Scene>();
}

void Game::Run()
{
    SDL_GL_SetSwapInterval(60);
    float last = window->GetTime();
    float now = 0;
    float deltaTime = 0;

    while (window->IsOpen())
    {
        // PRE FRAME
        window->UpdateEvents();
        
        glClearColor(PRIMARY_COLOR.x, PRIMARY_COLOR.y, PRIMARY_COLOR.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        now = window->GetTime();
        deltaTime = now - last; 
        last = now;
        
        scene->Update(deltaTime);
        scene->Render();
        
        // POST FRAME
        window->Update();
        input->Update();
        
        INFO("FPS: %f", 1.0f / deltaTime);
    }
}