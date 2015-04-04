#include "game_pawn.h"

GamePawn::GamePawn() : aliveTime(5.0f), Score(1), Position(0, 0), Size(1, 1), Color(1.0f), Rotation(0.0f), Sprite(), isDestroyed(GL_FALSE)
{

}

GamePawn::GamePawn(GLfloat alivetime, GLuint score, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color) : aliveTime(alivetime), Score(score), Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite), isDestroyed(GL_FALSE)
{

}

GLvoid GamePawn::Draw(SpriteRender &renderer)
{
    renderer.Draw(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}