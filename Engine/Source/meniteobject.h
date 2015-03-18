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
class Menite2DObject
{
    public:
        GLvoid addVertexData(ME2Dpos position);
        GLvoid addVertexData(ME2Dpos position, MErgb color);
        GLvoid addVertexData(ME2Dpos position, MErgb color, ME2Dpos texture);
        GLvoid addIndexDraw(GLuint index);
        GLvoid removeIndexDraw(GLuint index);
};

#endif MENITE_OBJECT