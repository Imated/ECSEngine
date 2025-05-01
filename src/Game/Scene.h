#pragma once
#include "Rendering/Renderer.h"
#include "Rendering/Window.h"

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(Window* window, Renderer* renderer);
};
