#include "SpriteComponent.h"

#include "TransformComponent.h"
#include "glm/gtx/string_cast.hpp"
#include "Rendering/Renderer.h"

void SpriteComponent::render(Entity& e, Window& window, Renderer& renderer)
{
    if(shader == nullptr)
        shader = renderer.getDefaultShader();
    shader->Activate();
    float width = window.GetSize().x;
    float height = window.GetSize().y;
    glm::mat4x4 projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    glm::mat4x4 mvp = projection;
    mvp *= e.GetComponent<TransformComponent>()->getTransformationMatrix();
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
