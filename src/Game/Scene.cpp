﻿#include "Scene.h"

#include <random>

#include "Game.h"
#include "Components/Entity.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Input/Input.h"

Entity player;
TransformComponent* playerTransform;
SpriteComponent* playerRenderer;
float direction;
glm::vec2 velocity;
float last = 0;
Scene::Scene()
{
    player = Entity();
    playerTransform = player.GetComponent<TransformComponent>();
    playerRenderer = player.AddComponent<SpriteComponent>(new Texture("res/Player.png"));
    playerTransform->setScale(glm::vec3(1.0f));

    float randMin = -2.0f;
    float randMax = 2.0f;
    srand(static_cast<signed int>(time(nullptr)));
    float r = randMin + static_cast <float>(rand()) / (RAND_MAX / (randMax - randMin));
    direction = r;
    INFO("%f", direction);
}

void Scene::Update(float deltaTime)
{
    static float ROT_SPEED = 1.5f;
    static float MOVE_SPEED = 750.0f;
    static float ACCELERATION = 50.0f;
    Input& input = Game::GetInput();
    if(input.GetKey(SDLK_a))
    {
        playerTransform->setRotation(playerTransform->getRotation().z - ROT_SPEED * deltaTime);
        direction = ROT_SPEED / 1.5f;
    }
    else if(input.GetKey(SDLK_d))
    {
        playerTransform->setRotation(playerTransform->getRotation().z + ROT_SPEED * deltaTime);
        direction = -ROT_SPEED / 1.5f;
    }
    else
    {
        playerTransform->setRotation(playerTransform->getRotation().z - direction * deltaTime);
    }

    if(input.GetKey(SDLK_SPACE))
    {
        velocity += glm::vec2(sin(playerTransform->getRotation().z), -cos(playerTransform->getRotation().z)) * ACCELERATION * deltaTime;
        velocity = glm::vec2(glm::clamp(velocity.x, -MOVE_SPEED, MOVE_SPEED), glm::clamp(velocity.y, -MOVE_SPEED, MOVE_SPEED));
    }
    playerTransform->setPosition(glm::vec3(playerTransform->getPosition().x + velocity.x * deltaTime, playerTransform->getPosition().y + velocity.y * deltaTime, 0.0f));
}

void Scene::Render()
{
    playerRenderer->render(0, player, Game::GetWindow());
}