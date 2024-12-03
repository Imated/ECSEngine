#include "SpriteComponent.h"

#include "TransformComponent.h"
#include "glm/gtx/string_cast.hpp"

SpriteComponent::~SpriteComponent()
{
    shader.Delete();
}

void SpriteComponent::Initialize(Entity& e)
{
    shader = Shader("res/Default.vert", "res/Default.frag");
    GLuint VBO;
    GLuint EBO;
    auto topLeft = glm::vec2(0);
    auto topRight = glm::vec2(0);
    auto bottomLeft = glm::vec2(0);
    auto bottomRight = glm::vec2(0);

    float x = 0;
    float y = 0;
    topLeft = glm::vec2(x, y);
    topRight = glm::vec2(x + 32, y); // w
    bottomLeft = glm::vec2(x, y + 32); // h
    bottomRight = glm::vec2(x + 32, y + 32); // w, h
    
    GLfloat vertices[] =
    {
        // Positions                  // UV Coordinates
        topLeft.x, topLeft.y,          0.0f, 1.0f,  // Top Left
        topRight.x, topRight.y,        1.0f, 1.0f,  // Top Right
        bottomLeft.x, bottomLeft.y,    0.0f, 0.0f,  // Bottom Left
        bottomRight.x, bottomRight.y,  1.0f, 0.0f   // Bottom Right
    };

    constexpr GLuint indices[] =
    {
        0, 1, 2, // Top Left, Top Right, Bottom Left
        1, 3, 2   // Top Right, Bottom Right, Bottom Left
    };

    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteComponent::Render(float deltaTime, Entity& e, Window& window)
{
    shader.Activate();
    const float aspectRatio = window.GetAspectRatio();
    float width = window.GetSize().x;
    float height = window.GetSize().y;
    glm::mat4x4 projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
    glm::mat4x4 mvp = projection;
    mvp *= e.GetComponent<TransformComponent>()->GetTransformationMatrix();
    shader.SetMatrix4x4("mvp", value_ptr(mvp));
    
    if(texture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
        texture->Use();
        shader.SetBool("useTexture", true);
    }
    else
        shader.SetBool("useTexture", false);
    glBindVertexArray(quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
