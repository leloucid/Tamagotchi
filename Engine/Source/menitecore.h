/****
    Menite - Core
    -------------
    Use for included all require library outside the solution.
    Defined the pre-processive directive, typedef, template,
    global scope variable and the basic function to call engine.
****/

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
} MEwindow;

/* Menite pointer */
typedef GLvoid (*MEptr);

/**
    Menite variable and function
**/

extern MEwindow meniteWindow;

GLvoid MeniteInit(GLuint width, GLuint height, GLchar* title);
GLvoid MeniteExecute();
GLvoid MeniteStop();