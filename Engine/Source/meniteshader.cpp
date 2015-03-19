#include "meniteshader.h"

MEshader::MEshader(const GLchar *vertexSource, const GLchar *fragmentSource)
{
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShader, 1, &vertexSource, nullptr);
    if (meniteWindow.mode == MENITE_DEBUG) puts("Vertex source code loaded.");

    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShader, 1, &fragmentSource, nullptr);
    if (meniteWindow.mode == MENITE_DEBUG) puts("Fragment source code loaded.");

    this->vertexLoaded = GL_TRUE;
    this->fragmentLoaded = GL_TRUE;
}

GLvoid MEshader::insertSource(MEshadertype type, GLchar *source)
{
    switch (type)
    {
        case VERTEX_SHADER:
            if (!this->vertexLoaded) this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(this->vertexShader, 1, &source, nullptr);
            this->vertexLoaded = GL_TRUE;
            if (meniteWindow.mode == MENITE_DEBUG) puts("Vertex source code loaded.");
            break;
        case FRAGMENT_SHADER:
            if (!this->fragmentLoaded) this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(this->fragmentShader, 1, &source, nullptr);
            this->fragmentLoaded = GL_TRUE;
            if (meniteWindow.mode == MENITE_DEBUG) puts("Fragment source code loaded.");
            break;
    }
}

GLvoid MEshader::useShader()
{
    if (!this->shaderIsBuilt)
    {
        this->shaderProgram = glCreateProgram();

        if (this->vertexLoaded)
        {
            glCompileShader(this->vertexShader);
            glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(this->vertexShader, 512, NULL, infoLog);
                puts("Error: Vertex shader compilation failed.");
                puts(infoLog);
            }
            else glAttachShader(this->shaderProgram, this->vertexShader);
        }

        if (this->fragmentLoaded)
        {
            glCompileShader(this->fragmentShader);
            glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
                puts("Error: Fragment shader compilation failed.");
                puts(infoLog);
            }
            else glAttachShader(this->shaderProgram, this->fragmentShader);
        }

        glLinkProgram(this->shaderProgram);

        if (this->vertexLoaded) glDeleteShader(this->vertexShader);
        if (this->fragmentLoaded) glDeleteShader(this->fragmentShader);

        this->shaderIsBuilt = GL_TRUE;
    }
    
    glUseProgram(this->shaderProgram);
}

MEshader::~MEshader()
{
    glDeleteProgram(this->shaderProgram);
}