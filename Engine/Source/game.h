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

//#include "game_theme.h"
#include "game_pawn.h"

enum GameLevel { MENU_LV, THEME_LV, MODE_LV, PLAY_LV };
enum GameMode { TIME_ATTACK, ENDLESS };
enum PlayState { PLAY, PAUSE, END };

class Game
{
    public:
        // Game State
        GameLevel Currentlevel;
        GLuint Currenttheme;
        GameMode Currentmode;
        PlayState CurrentPlayState;
        GLuint Score;
        GLint Lives;
        GLfloat Time;
        //std::vector<GameTheme> Themes;
        std::vector<GamePawn> Pawn;
        // Load theme/mode (use before game level)
        GLvoid LoadTheme();
        GLvoid LoadMode();
        // Draw level
        GLvoid DrawCurrentLevel(GLfloat dt);
        // Pawn in game
        GLvoid SpawnPawn(GLfloat dt);
        // Game State
        GLboolean Keys[1024], Keysprocessed[1024];
        // Game Configure
        GLuint windowWidth, windowHeight;
        // Constructor/Deconstructor
        Game(GLuint width, GLuint height);
        ~Game();
        // Initialize game state (shaders/textures/sounds/levels)
        GLvoid init();
        // Initialize game theme
        GLvoid LoadGameTheme(GLchar *PathToGameTheme);
        // GameLoop
        GLvoid ProcessInput();
        GLvoid Update(GLfloat dt);
        GLvoid Render(GLfloat dt);
        // Reset
        GLvoid ResetGame();
};

#endif GAME