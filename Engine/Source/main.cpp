#include "main.h"
#include <mxml.h>

Game Hittheshapes(1024, 768);

// Window declerations
GLFWwindow* window;

// GLFW function declerations
GLvoid key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode);
GLvoid mouse_button_callback(GLFWwindow* window, GLint button, GLint action, GLint mods);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    Makewindow();
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Configure OpenGL
    glViewport(0, 0, Hittheshapes.windowWidth, Hittheshapes.windowHeight);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // DeltaTime
    GLfloat currentFrame;
    GLfloat DeltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    Hittheshapes.init();

    Hittheshapes.CurrentPlayState = PLAY;
    Hittheshapes.Currentmode = ENDLESS;
    if (Hittheshapes.Currentmode == TIME_ATTACK) Hittheshapes.Time = 30.0f;
    else if (Hittheshapes.Currentmode == ENDLESS) Hittheshapes.Lives = 6;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate DeltaTime
        currentFrame = glfwGetTime();
        DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Process Input Events
        glfwPollEvents();
        Hittheshapes.ProcessInput();

        // Update Game
        Hittheshapes.Update(DeltaTime);

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Hittheshapes.Render(DeltaTime);

        // Swap to current buffer
        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

GLvoid Makewindow()
{
    window = glfwCreateWindow(Hittheshapes.windowWidth, Hittheshapes.windowHeight, "Hit the shapes!", nullptr, nullptr);
}

GLFWwindow* Getwindow()
{
    return window;
}

GLvoid key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Hittheshapes.Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
        {
            Hittheshapes.Keys[key] = GL_FALSE;
            Hittheshapes.Keysprocessed[key] = GL_FALSE;
        }
    }
}

GLvoid mouse_button_callback(GLFWwindow* window, GLint button, GLint action, GLint mods)
{
    if (button >= 0 && button <= 8)
    {
        if (action == GLFW_PRESS)
            Hittheshapes.Keys[button] = GL_TRUE;
        else if (action == GLFW_RELEASE)
        {
            Hittheshapes.Keys[button] = GL_FALSE;
            Hittheshapes.Keysprocessed[button] = GL_FALSE;
        }
    }
}