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
    Typedef
**/

/**
    Menite - Shader
    Class Defined
**/

/* Menite Shader class */
class MEshader
{
    public:
        // Constructor
        MEshader(const GLchar* vertexFile, const GLchar* fragmentFile);
        // Deconstuctor
        ~MEshader();
        // Function
        /* Set OpenGL to use this shader program */
        GLvoid useShader();
    protected:
        // Variable
        GLint success; // Success state of compilation
        GLchar infoLog[512]; // Info of compilation
        GLuint shaderProgram; // Shader program
};

#endif MENITE_SHADER