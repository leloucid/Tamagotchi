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

/* Menite shader type */
enum MEshadertype { VERTEX_SHADER, FRAGMENT_SHADER };

/**
    Menite - Shader
    Class Defined
**/

/* Menite Shader class */
class MEshader
{
    public:
        // Constructor
        MEshader(const GLchar* vertexSource, const GLchar* fragmentSource);
        // Deconstuctor
        ~MEshader();
        // Function
        /* Insert source code into shader type */
        GLvoid insertSource(MEshadertype type, GLchar* source);
        /* Set OpenGL to use this shader program */
        GLvoid useShader();
    protected:
        // Variable
        GLint success; // Success state of compilation
        GLchar infoLog[512]; // Info of compilation
        GLuint shaderProgram, // Shader program
               vertexShader, // Vertex shader
               fragmentShader; // Fragment shader
        GLboolean shaderIsBuilt = GL_FALSE, // Is shader program build?
                  vertexLoaded = GL_FALSE, // Is vertex source code loaded?
                  fragmentLoaded = GL_FALSE; // Is fragment source code loaded?
};

#endif MENITE_SHADER