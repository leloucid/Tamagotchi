#include <iostream>

#include "shader.h"

Shader &Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

GLvoid Shader::Compile(const GLchar *vertexSource, const GLchar *fragmentSource)
{
    GLuint sVertex, sFragment;
    // vertex shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "VERTEX");
    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // delete shader
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

GLvoid Shader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
GLvoid Shader::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
GLvoid Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
GLvoid Shader::SetVector2f(const GLchar *name, glm::vec2 &value, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
GLvoid Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
GLvoid Shader::SetVector3f(const GLchar *name, glm::vec3 &value, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
GLvoid Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
GLvoid Shader::SetVector4f(const GLchar *name, glm::vec4 &value, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
GLvoid Shader::SetMatrix4(const GLchar *name, glm::mat4 &matrix, GLboolean useShader)
{
    if (useShader) this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

GLvoid Shader::checkCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| Error::Shader: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| Error::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
