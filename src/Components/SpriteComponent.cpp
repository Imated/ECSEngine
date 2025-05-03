#include "SpriteComponent.h"

#include "Camera.h"
#include "TransformComponent.h"
#include "glm/gtx/string_cast.hpp"
#include "Rendering/Renderer.h"
#include "Rendering/ShaderLibrary.h"

SpriteComponent::SpriteComponent(Texture* texture): shader(nullptr), texture(texture)
{
    shader = ShaderLibrary::Get("default").get();
}

void SpriteComponent::render(Entity& e, Window& window, Camera* camera)
{
    if(!isActive)
        return;
    shader->Activate();
    glm::mat4x4 mvp = camera->getVP(window.GetSize().x, window.GetSize().y) * e.transform->getTransformationMatrix();
    shader->SetMatrix4x4("mvp", value_ptr(mvp));
    texture->bind();
    Renderer::renderQuad(texture->getWidth(), texture->getHeight());
}
