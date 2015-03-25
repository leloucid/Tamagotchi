#include <iostream>
#include "meniteshader.h"

MeniteShader::MeniteShader(const GLchar *vertexSource, const GLchar *fragmentSource)
{
    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER), 
           fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint success;
    GLchar complieinfo[512];
    this->shaderprogram = glCreateProgram();

    glShaderSource(vertexshader, 1, &vertexSource, NULL);
    glCompileShader(vertexshader);
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexshader, 512, NULL, complieinfo);
        puts("Error: vertex shader compile failed.");
        puts(complieinfo);
    }
    else glAttachShader(this->shaderprogram, vertexshader);

    glShaderSource(fragmentshader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentshader);
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentshader, 512, NULL, complieinfo);
        puts("Error: fragment shader compile failed.");
        puts(complieinfo);
    }
    else glAttachShader(this->shaderprogram, fragmentshader);
    
    glLinkProgram(this->shaderprogram);
    glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderprogram, 512, NULL, complieinfo);
        puts("Error: fragment shader compile failed.");
        puts(complieinfo);
    }

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
}

GLvoid MeniteShader::useShader()
{
    glUseProgram(this->shaderprogram);
}

GLuint MeniteShader::getShaderProgram()
{
    return this->shaderprogram;
}

MeniteShader::~MeniteShader()
{
    glDeleteProgram(this->shaderprogram);
}