#include "menitecore.h"

GLFWwindow *window;
GLuint windowwidth, windowheight;

GLvoid MeniteInit(GLuint width, GLuint height, GLchar *title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    windowwidth = width;
    windowheight = height;

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
}

GLFWwindow *MeniteGetWindow()
{
    return window;
}

GLuint MeniteGetWindowWidth()
{
    return windowwidth;
}

GLuint MeniteGetWindowHeight()
{
    return windowheight;
}