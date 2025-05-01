#include "TransformComponent.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Rendering/Renderer.h"

TransformComponent::TransformComponent() = default;

TransformComponent::~TransformComponent() = default;

void TransformComponent::initialize(Entity& e)
{
    recalculateTransformationMatrix();
}

void TransformComponent::update(Entity& e) { }

void TransformComponent::setPosition(glm::vec3 newPosition)
{
    position = newPosition;
    recalculateTransformationMatrix();
}

void TransformComponent::setRotation(glm::vec3 newRotation)
{
    rotation = glm::quat(radians(newRotation));
    recalculateTransformationMatrix();
}

void TransformComponent::setRotation(float newRotation)
{
    auto euler = eulerAngles(rotation);
    euler.z = newRotation;
    rotation = glm::quat(euler);
    recalculateTransformationMatrix();
}

void TransformComponent::setScale(glm::vec3 newScale)
{
    _scale = newScale;
    recalculateTransformationMatrix();
}

void TransformComponent::recalculateTransformationMatrix()
{
    // GLint vp [4];
    // glGetIntegerv (GL_VIEWPORT, vp);
    glm::mat4 T = translate(glm::mat4(1.0f), position);
    glm::mat4 R = toMat4(rotation);
    glm::mat4 S = scale(glm::mat4(1.0f), _scale);
    transformationMatrix = T * R * S;
}
