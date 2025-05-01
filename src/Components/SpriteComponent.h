#pragma once

#include "Entity.h"
#include "Rendering/Texture.h"

class Window;
class Renderer;
class Shader;
class Component;

class SpriteComponent : public Component
{
public:
    SpriteComponent(Texture* texture = nullptr) : texture(texture) { }

    void render(Entity& e, Window& window, Renderer& renderer);

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
