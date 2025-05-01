#pragma once
#include "Entity.h"
#include "glm/fwd.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Rendering/Renderer.h"

class TransformComponent : public Component
{
public:
    TransformComponent();
    ~TransformComponent() override;

    void initialize(Entity& e) override;
    void update(Entity& e) override;
    
    void setPosition(glm::vec3 newPosition);
    void setRotation(glm::vec3 newRotation);
    void setRotation(float newRotation);
    void setScale(glm::vec3 newScale);

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return eulerAngles(rotation); }
    glm::quat getRotationQuat() const { return rotation; }
    glm::vec3 getScale() const { return _scale; }
    glm::mat4x4 getTransformationMatrix() const { return transformationMatrix; }
private:
    void recalculateTransformationMatrix();
    glm::vec3 position = glm::vec3(0);
    glm::quat rotation = glm::quat(glm::vec3(0));
    glm::vec3 _scale = glm::vec3(1);
    glm::mat4 transformationMatrix = glm::mat4(0);
};
