#ifndef MENITE_OBJECT
#define MENITE_OBJECT

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "meniteshader.h"

typedef struct MeniteRGB
{
    GLfloat red = 0.0f, green = 0.0f, blue = 0.0f;
} MeniteRGB;

class Menite2DSprite
{
    public:
        Menite2DSprite() {};
        Menite2DSprite(GLuint pos_x, GLuint pos_y, GLuint width, GLuint height, GLchar *hexcolor);
        ~Menite2DSprite();
        GLvoid loadTexture(const char *texturePath);
        GLvoid Draw(MeniteShader &shader);
    protected:
        GLuint VAO, VBO, EBO,
               pos_x, pos_y,
               width, height;
        MeniteRGB color;
        GLboolean textureLoaded = GL_FALSE;
        GLuint texture = NULL;
        GLboolean isInitData = GL_FALSE;
};

MeniteRGB HextoRGBColor(GLchar *hexcolor);

#endif MENITE_OBJECT