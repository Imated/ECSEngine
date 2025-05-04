#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Rendering/Renderer.h"
#include "Rendering/Window.h"
#include "Utils/Logger.h"
#include "Components/TransformComponent.h"

class Entity;
class Component;

class Entity
{
public:
    Entity()
    {
        transform = AddComponent<TransformComponent>();
    }

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component!");
        components.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        T* component = GetComponent<T>();
        component->initialize(*this);
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

    template <typename T, typename... Args>
    Entity&& WithComponent(Args&&... args)
    {
        AddComponent<T>(std::forward<Args>(args)...);
        return std::move(*this);
    }
    
    void update()
    {
        for (const auto& component : components)
        {
            if(component->isActive && isActive)
                component->update(*this);
        }
    }

    TransformComponent* transform;
    bool isActive = true;
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
