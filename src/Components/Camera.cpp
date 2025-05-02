#include "Camera.h"

Camera::Camera(bool makePrimary)
{
    isPrimary = makePrimary;
}

glm::mat4 Camera::getViewMatrix() const
{
    return translate(glm::mat4(1.0f), glm::vec3(-position, 0.0f));
}

glm::mat4 Camera::getProjection(float screenWidth, float screenHeight) const
{
    float halfW = screenWidth / (2.0f * zoom);
    float halfH = screenHeight / (2.0f * zoom);
    return glm::ortho(-halfW, halfW, halfH, -halfH, -1.0f, 1.0f);
}

glm::mat4 Camera::getVP(float screenWidth, float screenHeight) const
{
    return getProjection(screenWidth, screenHeight) * getViewMatrix();
}

