#pragma once
#include <memory>

#include "Scene.h"
#include "glm/vec2.hpp"
#include "Input/Input.h"
#include "Rendering/Window.h"

class Window;

class Game
{
private:
    static std::unique_ptr<Window> window;
    static std::unique_ptr<Input> input;
    static std::unique_ptr<Scene> scene;

public:

    Game(Window* wnd);
    void Run();

    void Update(float dt);
    void Render();

    static glm::vec2 GetWindowSize() { return window->GetSize(); }
    static Window& GetWindow() { return *window; }
    static Input& GetInput() { return *input; }
    static Scene& GetScene() { return *scene; }

};
