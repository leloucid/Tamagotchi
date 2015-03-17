#include "menitecore.h"

MEwindow meniteWindow;

GLvoid MeniteInit(GLuint width, GLuint height, GLchar* title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    meniteWindow.window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(meniteWindow.window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
}

GLvoid MeniteExecute()
{
    while (!glfwWindowShouldClose(meniteWindow.window))
    {
        glfwPollEvents();

        glfwSwapBuffers(meniteWindow.window);
    }

    glfwTerminate();
}

GLvoid MeniteStop()
{
    glfwSetWindowShouldClose(meniteWindow.window, GL_TRUE);
}