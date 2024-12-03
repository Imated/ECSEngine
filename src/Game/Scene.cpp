#include "Scene.h"

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
    playerTransform->SetScale(glm::vec3(1.0f));

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
    static float MOVE_SPEED = 0.75f;
    static float ACCELERATION = 0.15f;
    Input& input = Game::GetInput();
    if(input.GetKey(SDLK_a))
    {
        playerTransform->SetRotationZ(playerTransform->GetRotationZ() + ROT_SPEED * deltaTime);
        direction = ROT_SPEED / 1.5f;
    }
    else if(input.GetKey(SDLK_d))
    {
        playerTransform->SetRotationZ(playerTransform->GetRotationZ() - ROT_SPEED * deltaTime);
        direction = -ROT_SPEED / 1.5f;
    }
    else
    {
        playerTransform->SetRotationZ(playerTransform->GetRotationZ() + direction * deltaTime);
    }

    if(input.GetKey(SDLK_SPACE))
    {
        velocity += glm::vec2(-sin(playerTransform->GetRotationZ()), cos(playerTransform->GetRotationZ())) * ACCELERATION * deltaTime;
        velocity = glm::vec2(glm::clamp(velocity.x, -MOVE_SPEED, MOVE_SPEED), glm::clamp(velocity.y, -MOVE_SPEED, MOVE_SPEED));
    }
    playerTransform->SetPosition(glm::vec3(playerTransform->GetPosition().x + velocity.x * deltaTime, playerTransform->GetPosition().y + velocity.y * deltaTime, 0.0f));
}

void Scene::Render()
{
    playerRenderer->Render(0, player, Game::GetWindow());
}