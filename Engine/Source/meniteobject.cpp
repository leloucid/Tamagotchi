#include <iostream>
#include <string>

#include <SOIL\SOIL.h>

#include "meniteobject.h"
#include "menitecore.h"

Menite2DSprite::Menite2DSprite(GLuint pos_x, GLuint pos_y, GLuint width, GLuint height, GLchar *hexcolor)
{
    this->color = HextoRGBColor(hexcolor);
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->width = width;
    this->height = height;
}

GLvoid Menite2DSprite::loadTexture(const char *texturePath)
{
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    GLint width, height;
    unsigned char *texture = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(texture);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->textureLoaded = GL_TRUE;
}

GLvoid Menite2DSprite::Draw(MeniteShader &shader)
{
    if (!this->isInitData)
    {
        GLfloat vertices[] = {
            -1.0f,  1.0f,  0.0f,  1.0f,
             1.0f,  1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,  0.0f,
            -1.0f, -1.0f,  0.0f,  0.0f
        };
        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        this->isInitData = GL_TRUE;
    }
    shader.useShader();

    glUniform3f(glGetUniformLocation(shader.getShaderProgram(), "inColor"), this->color.red / 255.0f, this->color.green / 255.0f, this->color.blue / 255.0f);

    glUniform2f(glGetUniformLocation(shader.getShaderProgram(), "inPosition"), this->pos_x / (GLfloat)MeniteGetWindowWidth(), this->pos_y / (GLfloat)MeniteGetWindowHeight());
    glUniform2f(glGetUniformLocation(shader.getShaderProgram(), "inSize"), this->width / (GLfloat)MeniteGetWindowWidth(), this->height / (GLfloat)MeniteGetWindowHeight());

    if (this->textureLoaded)
    {
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glUniform1i(glGetUniformLocation(shader.getShaderProgram(), "usedTexture"), GL_TRUE);
    }
    else glUniform1i(glGetUniformLocation(shader.getShaderProgram(), "usedTexture"), GL_FALSE);

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Menite2DSprite::~Menite2DSprite()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

MeniteRGB HextoRGBColor(GLchar *hexcolor)
{
    MeniteRGB color;
    GLint flipflop = 0, swapcolor = 0;
    for (int i = hexcolor[0] == '#' ? 1 : 0; i < strlen(hexcolor); i++)
    {
        switch (toupper(hexcolor[i]))
        {
        case 'A':
            swapcolor == 0 ? color.red += 10 : swapcolor == 1 ? color.green += 10 : color.blue += 10;
            break;
        case 'B':
            swapcolor == 0 ? color.red += 11 : swapcolor == 1 ? color.green += 11 : color.blue += 11;
            break;
        case 'C':
            swapcolor == 0 ? color.red += 12 : swapcolor == 1 ? color.green += 12 : color.blue += 12;
            break;
        case 'D':
            swapcolor == 0 ? color.red += 13 : swapcolor == 1 ? color.green += 13 : color.blue += 13;
            break;
        case 'E':
            swapcolor == 0 ? color.red += 14 : swapcolor == 1 ? color.green += 14 : color.blue += 14;
            break;
        case 'F':
            swapcolor == 0 ? color.red += 15 : swapcolor == 1 ? color.green += 15 : color.blue += 15;
            break;
        default:
            swapcolor == 0 ? color.red += (hexcolor[i] - '0') : swapcolor == 1 ? color.green += (hexcolor[i] - '0') : color.blue += (hexcolor[i] - '0');
            break;
        }
        flipflop == 0 ? swapcolor == 0 ? color.red *= 16 : swapcolor == 1 ? color.green *= 16 : color.blue *= 16 : 0;
        flipflop == 1 ? swapcolor++ : 0;
        flipflop == 0 ? flipflop++ : flipflop --;
    }

    return color;
}