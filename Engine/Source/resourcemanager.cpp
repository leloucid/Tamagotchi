#include "resourcemanager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL\SOIL.h>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *vFragmentFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, vFragmentFile);
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

GLvoid ResourceManager::DeleteTexture(std::string name)
{
    glDeleteTextures(1, &Textures[name].ID);
}

GLvoid ResourceManager::Clear()
{
    for (auto iter : Shaders) glDeleteProgram(iter.second.ID);
    for (auto iter : Textures) glDeleteTextures(1, &iter.second.ID);
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

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // Load image
    int width, height;
    unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    // Now generate texture
    texture.Generate(width, height, image);
    // And finally free image data
    SOIL_free_image_data(image);
    return texture;
}