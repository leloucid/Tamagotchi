/****
    Menite - Object
    -------------
    Contains simple 2D shapes & object.
****/

#ifndef MENITE_OBJECT
#define MENITE_OBJECT

/**
    Include Core
**/

#include "menitecore.h"
#include "meniteshader.h"

/**
    Pre-processive directive
**/

/**
    Typedef
**/

/**
    Menite - Object
    Class Defined
**/

/* Menite 2D Object class */
class ME2Dobject
{
    public:
        GLvoid addVertexData(ME2Dpos position);
        GLvoid addVertexData(ME2Dpos position, MErgb color);
        GLvoid addVertexData(ME2Dpos position, MErgb color, ME2Dpos texture);
        GLvoid removeVertexData(GLuint index);
        GLvoid addIndexDraw(GLuint index);
        GLvoid removeIndexDraw(GLuint index);
        GLvoid draw(MEshader shader);
    protected:
        GLuint VAO, VBO, EBO, texture;
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        MEimage texture;
        GLint tWidth, tHeight;
        GLboolean textureLoaded = GL_FALSE;
};

#endif MENITE_OBJECT