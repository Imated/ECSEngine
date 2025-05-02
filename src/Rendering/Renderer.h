#pragma once

#include <memory>
#include <vector>
#include "Shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

class Renderer
{
public:
    Renderer();

    void renderQuad(float width, float height);
    std::shared_ptr<Shader> defaultShader;

private:
    GLuint quadVAO = 0;
    GLuint quadVBO = 0;
};
