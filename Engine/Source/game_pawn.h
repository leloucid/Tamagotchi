#ifndef GAME_PAWN
#define GAME_PAWN

#include <GL\glew.h>
#include <GLM\glm.hpp>

#include "texture.h"
#include "spriterender.h"

class GamePawn
{
    public:
        // Pawn State
        glm::vec2 Position, Size, Velocity;
        glm::vec3 Color, ColorID;
        GLfloat Rotation, aliveTime;
        GLuint Score;
        GLboolean isDestroyed;
        // Texture
        Texture2D Sprite;
        // Constructor
        GamePawn();
        GamePawn(glm::vec3 colorID, GLfloat aliveTime, GLuint score, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
        // Draw sprite
        virtual GLvoid Draw(SpriteRender &renderer);
        // Draw color ID
        virtual GLvoid DrawColorID(SpriteRender &renderer);
};

#endif GAME_PAWN