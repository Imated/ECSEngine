#pragma once

#include "Camera.h"
#include "Component.h"
#include "Entity.h"
#include "Rendering/Texture.h"

class Window;
class Renderer;
class Shader;

class SpriteComponent : public Component
{
public:
    SpriteComponent(Texture* texture = nullptr) : texture(texture) { }

    void render(Entity& e, Window& window, Renderer& renderer, Camera* camera);

    void initialize(Entity& e) override { }
    void update(Entity& e) override { }
    
    Shader* GetShader() const
    {
        return shader;
    }

private:
    Shader* shader;
    Texture* texture;
};
