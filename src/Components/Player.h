#pragma once
#include "Component.h"

class Player : public Component
{
public:
    void initialize(Entity& e) override;
    void update(Entity& e) override;
private:

};
