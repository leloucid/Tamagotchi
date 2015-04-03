#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <string>

#include <GL\glew.h>

#include "shader.h"
#include "texture.h"

class ResourceManager
{
    private:
        ResourceManager();
        // Storage
        static std::map<std::string, Shader> Shaders;
        static std::map<std::string, Texture2D> Textures;
        // Load and generates a shader class from file
        static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *vFragmentFile);
        // Load a texture from file
        static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
    public:
        // Load (and generates) a shader program from source file.
        static Shader LoadShader(const GLchar *vShaderFile, const GLchar *vFragmentFile, std::string name);
        // Get a stored shader.
        static Shader GetShader(std::string name);
        // Loads (and generates) a texture from file
        static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
        // Get a stored texture.
        static Texture2D GetTexture(std::string name);
        // De-allocate texture.
        static GLvoid DeleteTexture(std::string name);
        // De-allocates all load resources.
        static GLvoid Clear();
};

#endif RESOURCE_MANAGER