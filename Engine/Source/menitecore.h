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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <conio.h>

/* GLEW */
#define GLEW_STATIC
#include <GL\glew.h>

/* GLFW */
#include <GLFW\glfw3.h>

/**
    Pre-processive directive
**/

#define MENITE_SET_DEBUGMODE 0
#define MENITE_RELEASE 0
#define MENITE_DEBUG 1

#define MENITE_SET_SCREENMODE 1
#define MENITE_FULLSCREEN 0
#define MENITE_WINDOWED 1

#define MENITE_SET_WINDOW_WIDTH 2
#define MENITE_SET_WINDOW_HEIGHT 3

/**
    Global scope function and variable
**/

GLvoid MeniteInit(GLchar *title);
GLvoid MeniteSetup(GLuint option, GLuint value);
GLvoid MeniteChangeScreenMode(GLuint mode);
GLvoid MeniteChangeResolution(GLuint width, GLuint height);
GLvoid MeniteExecute();
GLvoid MeniteStop();
GLboolean Menite_isDebugMode();
GLFWwindow *MeniteGetWindow();

#endif MENITE_CORE