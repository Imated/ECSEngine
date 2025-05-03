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
    ~Renderer();

    static void initialize();
    static void renderQuad(float width, float height);
    static void setClearColor(const glm::vec4& color);

private:
    static GLuint quadVAO;
    static GLuint quadVBO;
};
