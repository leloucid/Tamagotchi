#ifndef UI_BUTTON
#define UI_BUTTON

#include <GL\glew.h>
#include <GLM\glm.hpp>

#include "texture.h"
#include "spriterender.h"

class UIButton
{
    public:
        // Pawn State
        glm::vec2 Position, Size;
        glm::vec3 Color, ColorID;
        GLfloat Rotation;
        GLboolean isClicked;
        // Texture
        Texture2D Sprite;
        // Constructor
        UIButton();
        UIButton(glm::vec3 colorID, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
        // Draw sprite
        virtual GLvoid Draw(SpriteRender &renderer);
        // Draw color ID
        virtual GLvoid DrawColorID(SpriteRender &renderer);
};

#endif UI_BUTTON