#ifndef GAME
#define GAME

#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "game_theme.h"
//#include "game_mode.h"
//#include "game_pawn.h"

enum GameLevel { MAIN_MENU, THEME, MODE, GAME };
enum GameMode { TIME_ATTACK, ENDLESS };

class Game
{
    private:
        // Game State
        GameLevel Currentlevel;
        GLuint Currenttheme;
        GameMode Currentmode;
        GLuint score;
        // Game Configure
        GLuint windowWidth, windowHeight;
        //std::vector<GameTheme> Themes;
        //std::vector<GameMode> Mode;
        //std::vector<GamePawn> Pawn;
        // Load level/theme/mode (use before game level)
        GLvoid LoadTheme();
        GLvoid LoadLevel();
        GLvoid LoadMode();
        // Draw level
        GLvoid DrawCurrentLevel(GLfloat dt);
        // Update game level
        GLvoid UpdateGame(GLfloat dt);
        // Pawn in game
        GLvoid SpawnPawn();
        GLvoid UpdatePawn(GLfloat dt);
    public:
        // Constructor/Deconstructor
        Game(GLuint width, GLuint height);
        ~Game();
        // Initialize game state (shaders/textures/sounds/levels)
        GLvoid init();
        // Initialize game theme
        GLvoid LoadGameTheme(GLchar *PathToGameTheme);
        // GameLoop
        GLvoid DetectInput(GLfloat dt);
        GLvoid Update(GLfloat dt);
        GLvoid Render(GLfloat dt);
        // Reset
        GLvoid ResetGame();
        // Change level/theme/game mode
        GLvoid ChangeLevel(GameLevel level);
        GLvoid ChangeTheme(GLuint theme);
        GLvoid ChangeMode(GameMode mode);
};

#endif GAME