#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "menitecore.h"
#include "meniteshader.h"
#include "meniteobject.h"

const GLchar *Sprite2DVertexSource = "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\0";

const GLchar *Sprite2DFragmentSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    MeniteInit(800, 600, "Hit the shapes!");

    glfwSetKeyCallback(MeniteGetWindow(), key_callback);

    MeniteShader Sprite2DShader(Sprite2DVertexSource, Sprite2DFragmentSource);
    Menite2DSprite MyFirstSprite(Sprite2DShader);

    while (!glfwWindowShouldClose(MeniteGetWindow()))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        MyFirstSprite.Draw();
        
        glfwSwapBuffers(MeniteGetWindow());
    }

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}