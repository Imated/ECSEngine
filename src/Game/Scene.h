#pragma once
#include <unordered_map>

#include "Components/Camera.h"
#include "Components/Entity.h"
#include "Rendering/Renderer.h"
#include "Rendering/Window.h"

class Scene
{
public:
    Scene();

    void update();
    void render(Window* window, Camera* camera);
    void AddEntity(Entity& entity, uint64_t id);
    void RemoveEntity(uint64_t id);
private:
    std::unordered_map<uint64_t, Entity*> entities;
};
