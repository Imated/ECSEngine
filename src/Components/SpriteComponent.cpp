#include "SpriteComponent.h"

#include "Camera.h"
#include "TransformComponent.h"
#include "glm/gtx/string_cast.hpp"
#include "Rendering/Renderer.h"

void SpriteComponent::render(Entity& e, Window& window, Renderer& renderer, Camera* camera)
{
    if(shader == nullptr)
        shader = renderer.getDefaultShader();
    shader->Activate();
    const float width = window.GetSize().x;
    const float height = window.GetSize().y;
    glm::mat4x4 mvp = camera->getVP(width, height) * e.GetComponent<TransformComponent>()->getTransformationMatrix();
    shader->SetMatrix4x4("mvp", value_ptr(mvp));
    
    if(texture != nullptr)
    {
        texture->bind();
        shader->SetBool("useTexture", true);
    }
    else
        shader->SetBool("useTexture", false);

    renderer.renderQuad(texture->getWidth(), texture->getHeight());
    //renderer.renderQuad(1024, 1024);
}
