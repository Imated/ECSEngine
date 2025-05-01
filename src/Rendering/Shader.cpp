#include "Shader.h"

Shader::Shader(const char* vertexFilename, const char* fragmentFilename)
{
    shaderID = glCreateProgram();
    const auto vertexShader = CreateShader(vertexFilename, GL_VERTEX_SHADER);
    const auto fragmentShader = CreateShader(fragmentFilename, GL_FRAGMENT_SHADER);
    
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::CreateShader(const char* filename, GLenum type) const
{
    const std::string source = readFile(filename);
    const char* shaderSource = source.c_str();

    GLint isCompiled = 0;
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog.data());
        ERRORMSG(errorLog.data());
        ERRORMSG("Could not compile shader!");
    }
    return shader;
}

#pragma region Shader Attributes
int Shader::GetUniformLocation(const char* name) const
{
    const int location = glGetUniformLocation(shaderID, name);
    if (location == -1)
    {
        std::string msg = "Could not find uniform variable with name of '" + std::string(name) + "'! Not loading shader...";
        const char* warningLog = msg.c_str();
        WARN(warningLog);
    }
    return location;
}

void Shader::SetMatrix4x4(const char* name, const float* matrix) const
{
    const int location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Shader::SetVector4(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
    const int location = GetUniformLocation(name);
    glUniform4f(location, x, y, z, w);
}

void Shader::SetVector3(const char* name, GLfloat x, GLfloat y, GLfloat z) const
{
    const int location = GetUniformLocation(name);
    glUniform3f(location, x, y, z);
}

void Shader::SetVector2(const char* name, GLfloat x, GLfloat y) const
{
    const int location = GetUniformLocation(name);
    glUniform2f(location, x, y);
}

void Shader::SetFloat(const char* name, float value) const
{
    const int location = GetUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::SetBool(const char* name, bool value) const
{
    const int location = GetUniformLocation(name);
    glUniform1i(location, value);
}
#pragma endregion

void Shader::Activate() const
{
    glUseProgram(shaderID);
}

void Shader::Delete() const
{
    glDeleteProgram(shaderID);
}
