#include "Texture.h"

#include <iostream>

#include "../libs/stb_image.h"
#include "Utils/Logger.h"

void LogError()
{
    switch (glGetError())
    {
    case GL_INVALID_ENUM:
        INFO("Texture Error: Invalid Enum.");
        break;
    case GL_INVALID_VALUE:
        INFO("Texture Error: Invalid Value.");
        break;
    case GL_INVALID_OPERATION:
        INFO("Texture Error: Invalid Operation.");
        break;
    case GL_STACK_OVERFLOW:
        INFO("Texture Error: Stack Overflow.");
        break;
    case GL_STACK_UNDERFLOW:
        INFO("Texture Error: Stack Underflow.");
        break;
    case GL_OUT_OF_MEMORY:
        INFO("Texture Error: Out Of Viable Memory.");
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        INFO("Texture Error: Invalid Framebuffer Operation.");
        break;
    case GL_CONTEXT_LOST:
        INFO("Texture Error: OpenGL Context Lost, the graphics card has reset.");
        break;
    default: ;
    }
}

Texture::Texture(const char* filename, GLint wrapMode, GLint filterMode)
{
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data == nullptr)
        ERRORMSG("Couldn't load texture!");
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

    float borderColor[] = {PRIMARY_COLOR.x, PRIMARY_COLOR.y, PRIMARY_COLOR.z, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    
    LogError();
    INFO("Texture Loaded.");
}

Texture::~Texture()
{
    stbi_image_free(data);
}

void Texture::Use() const
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    LogError();
}
