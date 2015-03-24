/****
    Menite - Shader
    -------------
    Use to create a shader program class.
    By insert each shader source code and build the shader program.
****/

#ifndef MENITE_SHADER
#define MENITE_SHADER

/**
    Include Core
**/

#include "menitecore.h"

/**
    Menite Shader class
**/

class MeniteShader
{
    public:
        // Constructor
        MeniteShader(const GLchar* vertexFile, const GLchar* fragmentFile);
        // Deconstuctor
        ~MeniteShader();
        // Function
        GLvoid useShader();
    protected:
        // Variable
        GLint success;
        GLchar infoLog[512];
        GLuint shaderProgram;
};

#endif MENITE_SHADER