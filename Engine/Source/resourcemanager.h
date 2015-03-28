#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <string>

#include <GL\glew.h>

#include "shader.h"
//#include "texture.h"

class ResourceManager
{
    private:
        ResourceManager();
        // Storage
        static std::map<std::string, Shader> Shaders;
        // Load and generates a shader class from file
        static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *vFragmentFile);
    public:
        // Load (and generates) a shader program from source file.
        static Shader LoadShader(const GLchar *vShaderFile, const GLchar *vFragmentFile, std::string name);
        // Get a stored shader.
        static Shader GetShader(std::string name);
        // De-allocates all load resources.
        static GLvoid Clear();
};

#endif RESOURCE_MANAGER