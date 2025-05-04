#include "Player.h"

#include "Entity.h"
#include "Game/Time.h"
#include "Input/Input.h"

void Player::initialize(Entity& e)
{
    
}

void Player::update(Entity& e)
{
    constexpr float rotSpeed = 1.5f;
    constexpr float moveSpeed = 75000.0f;
    constexpr float acceleration = 5000.0f;
    float direction = 0;
    glm::vec2 velocity = glm::vec2(0);
    float dt = Time::deltaTime;
     if(Input::GetKey(SDLK_a))
     {
         e.transform->setRotation(e.transform->getRotation().z - rotSpeed * dt);
         direction = rotSpeed / 1.5f;
     }
     else if(Input::GetKey(SDLK_d))
     {
         e.transform->setRotation(e.transform->getRotation().z + rotSpeed * dt);
         direction = -rotSpeed / 1.5f;
     }
     else
     {
         e.transform->setRotation(e.transform->getRotation().z - direction * dt);
     }
    
     if(Input::GetKey(SDLK_SPACE))
     {
         velocity += glm::vec2(sin(e.transform->getRotation().z), -cos(e.transform->getRotation().z)) * acceleration * dt;
         velocity = glm::vec2(glm::clamp(velocity.x, -moveSpeed, moveSpeed), glm::clamp(velocity.y, -moveSpeed, moveSpeed));
     }
    e.transform->setPosition(glm::vec3(e.transform->getPosition().x + velocity.x * dt, e.transform->getPosition().y + velocity.y * dt, 0.0f));
}
