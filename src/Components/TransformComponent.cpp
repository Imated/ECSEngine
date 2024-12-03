#include "TransformComponent.h"

#include "Game/Game.h"
#include "glm/gtc/matrix_transform.hpp"

TransformComponent::~TransformComponent()
{
    
}

void TransformComponent::Initialize(Entity& e)
{
    RecalculateTransformationMatrix();
}

void TransformComponent::Render(float deltaTime, Entity& e, Window& window)
{
    
}

void TransformComponent::SetPosition(glm::vec3 newPosition)
{
    position = newPosition;
    RecalculateTransformationMatrix();
}

void TransformComponent::SetPositionX(float newPosition)
{
    position.x = newPosition;
    RecalculateTransformationMatrix();
}

void TransformComponent::SetPositionY(float newPosition)
{
    position.y = newPosition;
    RecalculateTransformationMatrix();
}

void TransformComponent::SetRotation(glm::vec3 newRotation)
{
    rotation = newRotation;
    RecalculateTransformationMatrix();
}

void TransformComponent::SetRotationZ(float newRotation)
{
    rotation.z = newRotation;
    RecalculateTransformationMatrix();
}

void TransformComponent::SetScale(glm::vec3 newScale)
{
    scale = newScale;
    RecalculateTransformationMatrix();
}

void TransformComponent::RecalculateTransformationMatrix()
{
    transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, position);
    transformationMatrix = glm::rotate(transformationMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    transformationMatrix = glm::scale(transformationMatrix, scale);
}
