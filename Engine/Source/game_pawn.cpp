#include "game_pawn.h"

HTSpawn::HTSpawn(GLuint pos_x, GLuint pos_y, GLuint width, GLuint height, GLchar *hexcolor, const char *texturePath, GLuint score, GLuint lifetime)
{
    this->color = HextoRGBColor(hexcolor);
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->width = width;
    this->height = height;
    this->score = score;
    this->lifetime = lifetime;
    if (texturePath != NULL) this->loadTexture(texturePath);
}