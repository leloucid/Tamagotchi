#ifndef MENITE_SHADER
#define MENITE_SHADER

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MeniteShader
{
    public:
        MeniteShader(){};
        MeniteShader(const GLchar *vertexSource, const GLchar *fragmentSource);
        ~MeniteShader();
        GLvoid useShader();
        GLuint getShaderProgram();
    protected:
        GLuint shaderprogram;
};

#endif MENITE_CORE