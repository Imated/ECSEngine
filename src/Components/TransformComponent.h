#pragma once
#include "Entity.h"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

class TransformComponent : public Component
{
public:
    TransformComponent() { }
    ~TransformComponent() override;

    void Initialize(Entity& e) override;
    void Render(float deltaTime, Entity& e, Window& window) override;
    
    void SetPosition(glm::vec3 newPosition);
    void SetPositionX(float newPosition);
    void SetPositionY(float newPosition);
    void SetRotation(glm::vec3 newRotation);
    void SetRotationZ(float newRotation);
    void SetScale(glm::vec3 newScale);

    glm::vec3 GetPosition() const { return position; }
    float GetPositionX() const { return position.x; }
    float GetPositionY() const { return position.y; }
    glm::vec3 GetRotation() const { return rotation; }
    float GetRotationZ() const { return rotation.z; }
    glm::vec3 GetScale() const { return scale; }
    glm::mat4x4 GetTransformationMatrix() const { return transformationMatrix; }
private:
    void RecalculateTransformationMatrix();
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
    glm::mat4 transformationMatrix = glm::mat4(0);
};
