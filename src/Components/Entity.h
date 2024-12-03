#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Game/Game.h"
#include "Rendering/Window.h"
#include "Utils/Logger.h"

class TransformComponent;
class Entity;

class Component
{
public:
    virtual ~Component() = default;
    virtual void Initialize(Entity& e) = 0;
    virtual void Render(float deltaTime, Entity& e, Window& window) = 0;
};

class Entity
{
public:
    Entity()
    {
        AddComponent<TransformComponent>();
    }
    
    template <typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component!");
        components.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        T* component = GetComponent<T>();
        component->Initialize(*this);
        return component;
    }

    template <typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component!");
        auto removeIndex = GetIndexOf<T>();
        auto name = typeid(T).name();
        if(removeIndex == -1)
            WARN((std::string("There is no component to remove with type: ") + name).c_str());
        const auto backIndex = components.size() - 1;
        std::swap(components[removeIndex], components[backIndex]);
        components.pop_back();
    }
    
    template <typename T>
    T* GetComponent()
    {
        for (const auto& component : components)
        {
            if (auto derived = dynamic_cast<T*>(component.get()))
            {
                return derived;
            }
        }
        return nullptr;
    }

    template <typename T>
    bool HasComponent() const
    {
        for (const auto& component : components)
        {
            if (dynamic_cast<T*>(component.get()))
                return true;
        }
        return false;
    }
private:
    std::vector<std::unique_ptr<Component>> components;
    
    template <typename T>
    int GetIndexOf() const
    {
        for (int i = 0; i < components.size(); ++i)
        {
            auto component = components[i].get();
            if (dynamic_cast<T*>(component))
                return i;
        }
        return -1;
    }
};
