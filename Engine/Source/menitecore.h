#ifndef MENITE_CORE
#define MENITE_CORE

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLvoid MeniteInit(GLuint width, GLuint height, GLchar *title);
GLFWwindow *MeniteGetWindow();

#endif MENITE_CORE