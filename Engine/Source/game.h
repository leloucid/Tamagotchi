#ifndef GAME
#define GAME

#include <vector>
#include <cstdlib>
#include <cmath>

// debug
#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ui_button.h"
#include "game_pawn.h"

enum GameLevel { PLAY_LV };

class Game
{
    public:
        // Game State
        GameLevel Currentlevel;
        GLfloat RSCID_red = 1.0f, RSCID_green = 0.0f, RSCID_blue = 0.0f; // RSCID - Random Spawn ColorID - Used for click on object checking
        std::vector<UIButton> Buttons;
        std::vector<GamePawn> Pawns;
        // Draw level
        GLvoid DrawCurrentLevel(GLfloat dt);
        // Game State
        GLboolean Keys[1024], Keysprocessed[1024];
        // Game Configure
        GLuint windowWidth, windowHeight;
        // Constructor/Deconstructor
        Game(GLuint width, GLuint height);
        ~Game();
        // Initialize game state (shaders/textures/sounds/levels)
        GLvoid init();
        // GameLoop
        GLvoid ProcessInput();
        GLvoid Update(GLfloat dt);
        GLvoid Render(GLfloat dt);
        // Reset
        GLvoid ResetGame();
        // Change Level
        GLvoid ChangeLevel(GameLevel level);
    private:
        GLvoid ResetColorID();
};

#endif GAME