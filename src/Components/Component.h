#pragma once
class Entity;

class Component
{
public:
    virtual ~Component() = default;
    virtual void initialize(Entity& e) = 0;
    virtual void update(Entity& e) = 0;

    bool isActive = true;
};
