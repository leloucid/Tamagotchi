#ifndef SPRITE_RENDER
#define SPRITE_RENDER

#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "texture.h"

class SpriteRender
{
    private:
        // Render State
        Shader shader;
        GLuint VAO, VBO, EBO;
        // Initializes and configures
        GLvoid initRenderData();
    public:
        // Constructor/Deconstructor
        SpriteRender(Shader &shader);
        ~SpriteRender();
        // Renders a sprite
        GLvoid Draw(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};

#endif SPRITE_RENDER