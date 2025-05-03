#include "Scene.h"

#include <random>
#include <ranges>

#include "Components/SpriteComponent.h"

Scene::Scene()
{
    float randMin = -2.0f;
    float randMax = 2.0f;
    srand(static_cast<signed int>(time(nullptr)));
    float r = randMin + static_cast <float>(rand()) / (RAND_MAX / (randMax - randMin));
    //direction = r;
    //INFO("%f", direction);
}

void Scene::update()
{
    for (auto entity : entities)
    {
        entity.second->update();
    }
}

void Scene::render(Window* window, Camera* camera)
{
    for (auto entity : entities | std::views::values)
    {
        if(entity->HasComponent<SpriteComponent>())
            entity->GetComponent<SpriteComponent>()->render(*entity, *window, camera);
    }
}

void Scene::AddEntity(Entity& entity, uint64_t id)
{
    entities[id] = &entity;
}

void Scene::RemoveEntity(uint64_t id)
{
    entities.erase(id);
}
