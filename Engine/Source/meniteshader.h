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
    Pre-processive directive
**/

/**
    Typedef
**/
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
        GLint success;
        GLchar infoLog[512];
        GLuint shaderProgram,
               vertexShader,
               fragmentShader;
        GLboolean shaderIsBuilt = GL_FALSE,
                  vertexLoaded = GL_FALSE,
                  fragmentLoaded = GL_FALSE;
};

/**
    Menite - Shader
    Function Defined
**/

MErgb hexColortoRGB(GLchar *hexcolor);
MErgba hexColortoRGBA(GLchar *hexcolor, GLfloat alpha);

#endif MENITE_SHADER