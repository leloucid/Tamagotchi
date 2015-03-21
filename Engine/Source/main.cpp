/* Include Menite engine */
#include "meniteengine.h"

GLvoid initialfunction();
GLvoid executefunction();
GLvoid endfunction();

GLuint VAO, VBO, EBO;

int main()
{
    MeniteInit(800, 600, "Menite Engine", MENITE_DEBUG);

    MeniteExecute(executefunction);

    return 0;
}

GLvoid executefunction()
{
    // Initialize static variable
    static int number = 0;
    static GLboolean build = GL_FALSE;
    static MEshader shader("../Shader/simpleVertexShader.vert", "../Shader/simpleFragmentShader.frag");

    if (!build)
    {
        GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  // Top Right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom Left
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f   // Top Left 
        };
        GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

        glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

        build = GL_TRUE;
    }

    // Do some condition
    if (floor(glfwGetTime()) >= number)
    {
        printf("hi, Application run: %.0f second(s).\n", floor(glfwGetTime()));
        number++;
    }

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw our first triangle
    shader.useShader();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (glfwWindowShouldClose(meniteWindow.window))
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}