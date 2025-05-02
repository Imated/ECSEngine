#include "ShaderLibrary.h"
#include "Utils/Utility.h"

std::unordered_map<std::string, std::unordered_map<shaderType, std::string>> ShaderLibrary::shaderPaths;
std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderLibrary::shaders;

const std::shared_ptr<Shader>& ShaderLibrary::Get(const std::string& name)
{
    return shaders.at(name);
}

const std::shared_ptr<Shader>& ShaderLibrary::Load(const std::string& name, const std::unordered_map<shaderType, std::string>& paths)
{
    shaderPaths[name] = paths;
    Set(name, std::make_unique<Shader>(Shader(paths.at(Vertex).c_str(), paths.at(Fragment).c_str())));
    return Get(name);
}

void ShaderLibrary::Free(const std::string& name)
{
    shaderPaths.erase(name);
    shaders.erase(name);
}


void ShaderLibrary::Set(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    shaders[name] = shader;
}