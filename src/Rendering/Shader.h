#pragma once
#include "glad/glad.h"
#include "Utils/Utility.h"
#include "Utils/Logger.h"
#include "vector"

class Shader
{
public:
    GLuint shaderID;
    Shader(const char* vertexFilename, const char* fragmentFilename);
    Shader(): shaderID(0) { }

    void SetMatrix4x4(const char* name, const float* matrix) const;
    void SetVector4(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void SetVector3(const char* name, GLfloat x, GLfloat y, GLfloat z) const;
    void SetVector2(const char* name, GLfloat x, GLfloat y) const;
    void SetFloat(const char* name, float value) const;
    void SetBool(const char* name, bool value) const;
    
    void Activate() const;
    void Delete() const;
private:
    int GetUniformLocation(const char* name) const;
    GLuint CreateShader(const char* filename, GLenum type) const;
};
