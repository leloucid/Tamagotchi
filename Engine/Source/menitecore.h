/****
    Menite - Core
    -------------
    Use for included all require library outside the solution.
    Defined the pre-processive directive, typedef, template,
    global scope variable and the basic function to call engine.
****/

#ifndef MENITE_CORE
#define MENITE_CORE

/**
    Include library
**/

/* Standard library */
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

/* GLEW */
#define GLEW_STATIC
#include <GL\glew.h>

/* GLFW */
#include <GLFW\glfw3.h>

/**
    Pre-processive directive
**/
#define MENITE_RELEASE 0
#define MENITE_DEBUG 1

/**
    Typedef
**/

/* Menite 2D Position */
typedef struct ME2Dpos
{
    ME2Dpos() : x(0.0f), y(0.0f) {}
    GLfloat x;
    GLfloat y;
} ME2Dpos;

/* Menite image */
typedef unsigned char (*MEimage)();

/* Menite RGB */
typedef struct MErgb
{
    MErgb() : r(0.0f), g(0.0f), b(0.0f) {}
    GLfloat r;
    GLfloat g;
    GLfloat b;
} MErgb;

/* Menite RGB (with alpha) */
typedef struct MErgba
{
    MErgba() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
} MErgba;

/* Menite window */
typedef struct MEwindow{
    GLFWwindow *window;
    GLuint width;
    GLuint height;
    GLchar *title;
    GLuint mode;
} MEwindow;

/* Menite Execute function callback pointer */
typedef GLvoid (*MEEXEptr)();

/**
    Menite variable and function
**/

/* Menite window object */
extern MEwindow meniteWindow;

/* Initialize context */
GLvoid MeniteInit(GLuint width, GLuint height, GLchar* title, GLuint mode);

/* Execute game loop (with execute function for draw any game object and check any game event) */
GLvoid MeniteExecute(MEEXEptr initialfunction, MEEXEptr executefunction, MEEXEptr endfunction);

/* Stop game loop */
GLvoid MeniteStop();

#endif MENITE_CORE