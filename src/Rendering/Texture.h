#pragma once

#include "Constants.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION

class Texture
{
public:
    Texture(const char* filename, GLint wrapMode = GL_CLAMP_TO_BORDER, GLint filterMode = GL_NEAREST);
    ~Texture();

    void bind();
    
    GLuint GetHandle() const { return handle; }
    GLint getWidth() const { return width; }
    GLint getHeight() const { return height; }
private:
    GLuint handle = 0;
    GLint width;
    GLint height;
    unsigned char* data;
};