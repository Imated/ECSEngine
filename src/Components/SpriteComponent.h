#pragma once
#include <vector>
#include "Entity.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Window.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(Texture* texture = nullptr) : texture(texture) { }

    ~SpriteComponent() override;

    void Initialize(Entity& e) override;
    void Render(float deltaTime, Entity& e, Window& window) override;

    Shader GetShader() const
    {
        return shader;
    }

private:
    Shader shader;
    GLuint quadVAO = 0;
    Texture* texture;
};
