#include "meniteengine.h"

MEwindow meniteWindow;

GLvoid MeniteInit(GLuint width, GLuint height, GLchar* title, GLuint mode)
{
    if (mode == MENITE_DEBUG) meniteWindow.mode = MENITE_DEBUG;

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

GLvoid MeniteExecute(MEEXEptr initialfunction, MEEXEptr executefunction, MEEXEptr endfunction)
{
    initialfunction();

    while (!glfwWindowShouldClose(meniteWindow.window))
    {
        glfwPollEvents();

        executefunction();

        glfwSwapBuffers(meniteWindow.window);
    }

    endfunction();

    glfwTerminate();
}

GLvoid MeniteStop()
{
    glfwSetWindowShouldClose(meniteWindow.window, GL_TRUE);
}