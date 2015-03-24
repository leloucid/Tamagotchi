#ifndef MENITE_OBJECT
#define MENITE_OBJECT

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "meniteshader.h"

class Menite2DSprite
{
    public:
        Menite2DSprite(MeniteShader &shader);
        ~Menite2DSprite();
        GLvoid Draw();
    protected:
        GLuint VAO, VBO, EBO;
        MeniteShader shader;
};

#endif MENITE_OBJECT