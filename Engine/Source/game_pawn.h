#ifndef GAME_PAWN
#define GAME_PAWN

#include "meniteobject.h"

class HTSpawn : public Menite2DSprite
{
    public:
        HTSpawn(GLuint pos_x, GLuint pos_y, GLuint width, GLuint height, GLchar *hexcolor, const char *texturePath, GLuint score, GLuint lifetime);
    protected:
        GLuint score, lifetime;
        const char *texturePath = NULL;
};

#endif GAME_PAWN