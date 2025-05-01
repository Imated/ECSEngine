#pragma once
#include "Entity.h"
#include "glm/gtx/transform.hpp"

class Camera : public Component
{
public:

    Camera(bool makePrimary);

    void initialize(Entity& e) override { }
    void update(Entity& e) override { }
    
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjection(float screenWidth, float screenHeight) const;
    glm::mat4 getVP(float screenWidth, float screenHeight) const;

    bool isPrimary;
    glm::vec2 position = {0.0f, 0.0f};
    float zoom = 1.0f;
};
