#include "Player.h"

#include "Entity.h"
#include "Input/Input.h"

void Player::initialize(Entity& e)
{
    
}

void Player::update(Entity& e)
{
    constexpr float rotSpeed = 1.5f;
    constexpr float moveSpeed = 750.0f;
    constexpr float acceleration = 50.0f;
    float direction = 0;
    glm::vec2 velocity = glm::vec2(0);
     if(Input::GetKey(SDLK_a))
     {
         e.transform->setRotation(e.transform->getRotation().z - rotSpeed * 0.01f);
         direction = rotSpeed / 1.5f;
     }
     else if(Input::GetKey(SDLK_d))
     {
         e.transform->setRotation(e.transform->getRotation().z + rotSpeed * 0.01f);
         direction = -rotSpeed / 1.5f;
     }
     else
     {
         e.transform->setRotation(e.transform->getRotation().z - direction * 0.01f);
     }
    
     if(Input::GetKey(SDLK_SPACE))
     {
         velocity += glm::vec2(sin(e.transform->getRotation().z), -cos(e.transform->getRotation().z)) * acceleration * 0.01f;
         velocity = glm::vec2(glm::clamp(velocity.x, -moveSpeed, moveSpeed), glm::clamp(velocity.y, -moveSpeed, moveSpeed));
     }
    e.transform->setPosition(glm::vec3(e.transform->getPosition().x + velocity.x * 0.01f, e.transform->getPosition().y + velocity.y * 0.01f, 0.0f));
}
