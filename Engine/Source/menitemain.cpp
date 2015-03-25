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
    "layout (location = 1) in vec2 texposition;\n"
    "out vec2 texPosition;\n"
    "uniform vec2 inPosition;\n"
    "uniform vec2 inSize;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(((position.x + 1) * inSize.x) + (inPosition.x * 2) - 1, ((position.y - 1) * inSize.y) - (inPosition.y * 2) + 1, 0.0, 1.0);\n"
    "texPosition = texposition;\n"
    "}\0";

const GLchar *Sprite2DFragmentSource = "#version 330 core\n"
    "in vec2 texPosition;\n"
    "out vec4 color;\n"
    "uniform vec3 inColor;\n"
    "uniform bool usedTexture;\n"
    "uniform sampler2D inTexture;\n"
    "void main()\n"
    "{\n"
    "if(usedTexture)\n"
    "{\n"
    "color = texture(inTexture, texPosition);\n"
    "} else {\n"
    "color = vec4(inColor, 1.0f);\n"
    "}\n"
    "}\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    MeniteInit(800, 600, "Hit the shapes!");

    glfwSetKeyCallback(MeniteGetWindow(), key_callback);

    MeniteShader Sprite2DShader(Sprite2DVertexSource, Sprite2DFragmentSource);
    Menite2DSprite MySprite(200, 150, 400, 300, "#FF0044", Sprite2DShader);
    MySprite.loadTexture("../Image/container.jpg");

    while (!glfwWindowShouldClose(MeniteGetWindow()))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        MySprite.Draw();
        
        glfwSwapBuffers(MeniteGetWindow());
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}