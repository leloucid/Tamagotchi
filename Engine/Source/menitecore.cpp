#include "meniteengine.h"

GLFWwindow* window;
GLuint currentscreenmode = MENITE_WINDOWED;
GLuint currentdebugmode = MENITE_DEBUG;
GLchar* currenttitle = "Menite Engine";
GLuint currentwidth = 800;
GLuint currentheight = 600;

GLvoid MeniteInit(GLchar *title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(currentwidth, currentheight, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 600);

    currenttitle = title;
}

GLvoid MeniteSetup(GLuint option, GLuint value)
{
    switch (option)
    {
        case MENITE_SET_DEBUGMODE:
            currentdebugmode = value;
            break;
        case MENITE_SET_SCREENMODE:
            MeniteChangeScreenMode(value);
            currentscreenmode = value;
            break;
        case MENITE_SET_WINDOW_WIDTH:
            MeniteChangeResolution(value, currentheight);
            currentwidth = value;
            break;
        case MENITE_SET_WINDOW_HEIGHT:
            MeniteChangeResolution(currentwidth, value);
            currentheight = value;
            break;
    }
}

GLvoid MeniteChangeScreenMode(GLuint mode)
{
    if (mode == MENITE_FULLSCREEN && mode != currentscreenmode)
    {
        const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        GLFWwindow *twindow = glfwCreateWindow(vidmode->width, vidmode->height, currenttitle, glfwGetPrimaryMonitor(), nullptr);
        glfwDestroyWindow(window);
        window = twindow;

        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        glewInit();

        glViewport(0, 0, vidmode->width, vidmode->height);
    }
    else if (mode == MENITE_WINDOWED && mode != currentscreenmode)
    {
        GLFWwindow *twindow = glfwCreateWindow(currentwidth, currentheight, currenttitle, nullptr, nullptr);
        glfwDestroyWindow(window);
        window = twindow;

        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        glewInit();

        glViewport(0, 0, 800, 600);
    }
}

GLvoid MeniteChangeResolution(GLuint width, GLuint height)
{
    glfwSetWindowSize(window, width, height);
}

GLvoid MeniteExecute()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //MeniteGame.update();

        //MeniteGame.renderObject();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

GLvoid MeniteStop()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}

GLboolean Menite_isDebugMode()
{
    return currentdebugmode;
}

GLFWwindow *MeniteGetWindow()
{
    return window;
}