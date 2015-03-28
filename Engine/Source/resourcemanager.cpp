#include "resourcemanager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *vFragmentFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, vFragmentFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

GLvoid ResourceManager::Clear()
{
    for (auto iter : Shaders) glDeleteProgram(iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *vFragmentFile)
{
    std::string vertexSource, fragmentSource;

    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(vFragmentFile);
        // Read file's buffer contents into streams
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexSource = vShaderStream.str();
        fragmentSource = fShaderStream.str();
    }
    catch (std::exception e)
    {
        std::cout << "Error::Shader: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexSource.c_str();
    const GLchar *fShaderCode = fragmentSource.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}