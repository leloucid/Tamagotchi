#include "meniteshader.h"

MeniteShader::MeniteShader(const GLchar *vertexFile, const GLchar *fragmentFile)
{
    const GLchar *vertexSource, *fragmentSource;
    std::string vertexSourceBuffer, fragmentSourceBuffer;
    GLuint vertexShader, fragmentShader;

    try
    {
        std::ifstream vertex(vertexFile);
        std::ifstream fragment(fragmentFile);
        std::stringstream bvertex, bfragment;

        bvertex << vertex.rdbuf();
        bfragment << fragment.rdbuf();

        vertex.close();
        fragment.close();

        vertexSourceBuffer = bvertex.str();
        fragmentSourceBuffer = bfragment.str();
    }
    catch (std::exception e)
    {
        puts("Error: Shader file not successfully read.");
    }

    vertexSource = vertexSourceBuffer.c_str();
    fragmentSource = fragmentSourceBuffer.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

    this->shaderProgram = glCreateProgram();

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &this->success);
    if (!this->success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, this->infoLog);
        puts("Error: Vertex shader compilation failed.");
        puts(this->infoLog);
    }
    else glAttachShader(this->shaderProgram, vertexShader);

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &this->success);
    if (!this->success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, this->infoLog);
        puts("Error: Fragment shader compilation failed.");
        puts(this->infoLog);
    }
    else glAttachShader(this->shaderProgram, fragmentShader);

    glLinkProgram(this->shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLvoid MeniteShader::useShader()
{
    glUseProgram(this->shaderProgram);
}

MeniteShader::~MeniteShader()
{
    glDeleteProgram(this->shaderProgram);
}