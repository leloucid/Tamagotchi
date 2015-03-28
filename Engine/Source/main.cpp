#include "game.h"

Game Hittheshapes(1024, 768);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(Hittheshapes.windowWidth, Hittheshapes.windowHeight, "Hit the shapes!", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, Hittheshapes.windowWidth, Hittheshapes.windowHeight);

    // DeltaTime
    GLfloat currentFrame;
    GLfloat DeltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    Hittheshapes.init();

    while (!glfwWindowShouldClose(window))
    {
        // Calculate DeltaTime
        currentFrame = glfwGetTime();
        DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process Input Events
        glfwPollEvents();
        //Hittheshapes.DetectInput(DeltaTime);

        // Update Game
        //Hittheshapes.Update(DeltaTime);

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Hittheshapes.Render(DeltaTime);

        // Swap to current buffer
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}