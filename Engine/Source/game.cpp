#include "main.h"
#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
SpriteRender *ColorIDRenderer;
TextRender *TextRenderer;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(PLAY_LV), Currenttheme(0), Score(0)
{

}

Game::~Game()
{
    delete SpriteRenderer;
    delete ColorIDRenderer;
    delete TextRenderer;
}

GLvoid Game::init()
{
    // Load shaders
    ResourceManager::LoadShader("../Shader/sprite.vert", "../Shader/sprite.frag", "sprite");
    ResourceManager::LoadShader("../Shader/sprite.vert", "../Shader/colorid.frag", "colorid");
    // Load textures
    // Theme loaded
    ResourceManager::LoadTexture("../Images/milkyway-galaxy-bg.jpg", GL_FALSE, "theme_background");
    ResourceManager::LoadTexture("../Images/mimi1.png", GL_TRUE, "theme_pawn1");
    ResourceManager::LoadTexture("../Images/mimi2.png", GL_TRUE, "theme_pawn2");
    ResourceManager::LoadTexture("../Images/mimi3.png", GL_TRUE, "theme_pawn3");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->windowWidth), static_cast<GLfloat>(this->windowHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("colorid").Use().SetMatrix4("projection", projection);
    // Set render-specific controls
    SpriteRenderer = new SpriteRender(ResourceManager::GetShader("sprite"));
    ColorIDRenderer = new SpriteRender(ResourceManager::GetShader("colorid"));
    TextRenderer = new TextRender(this->windowWidth, this->windowHeight);
    TextRenderer->Load("../Font/supermarket.ttf", 128);
}

GLvoid Game::Update(GLfloat dt)
{
    if (this->Currentlevel == PLAY_LV)
    {
        if (this->Currentmode == TIME_ATTACK) 
        {
            if (this->CurrentPlayState == PLAY && this->Time > 0)
            {
                this->Time -= dt;
                this->SpawnPawn(dt);
            }
            else if (this->Time < 0)
            {
                this->Time = 0;
                this->CurrentPlayState = END;
            }
        }
        else if (this->Currentmode == ENDLESS)
        {
            if (this->CurrentPlayState == PLAY && this->Lives > 0)
            {
                this->Time += dt;
                this->SpawnPawn(dt);
            }
            else if (this->Lives < 0)
            {
                this->Lives = 0;
                this->CurrentPlayState = END;
            }
        }
        if (this->CurrentPlayState == PLAY)
        {
            // Reduce life time
            for (GamePawn &itr : this->Pawn)
            {
                if (itr.isDestroyed) continue;
                itr.aliveTime -= dt;
                if (itr.aliveTime <= 0) 
                {
                    if (this->Currentmode == ENDLESS) this->Lives -= 1;
                    itr.isDestroyed = GL_TRUE;
                }
            }
        }   
    }
}

GLvoid Game::Render(GLfloat dt)
{
    DrawCurrentLevel(dt);
}

GLvoid Game::ProcessInput()
{
    if (this->Keys[GLFW_MOUSE_BUTTON_LEFT] && !this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT])
    {
        if (this->Currentlevel == PLAY_LV)
        {
            if (this->CurrentPlayState == PLAY)
            {
                // Render the color ID
                for (GamePawn &itr : this->Pawn)
                {
                    // Skip the pawn that already destroyed
                    if (itr.isDestroyed) continue;
                    // Render pawn color to color ID
                    itr.DrawColorID(*ColorIDRenderer);
                }

                // Read Color pixel at cursor
                GLint viewport[4];
                GLubyte pixel[3];
                GLdouble xpos, ypos;
                glGetIntegerv(GL_VIEWPORT, viewport);
                glfwGetCursorPos(Getwindow(), &xpos, &ypos);
                glReadPixels(xpos, viewport[3] - ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void*)pixel);
                std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
                std::cout << "R: " << (int)pixel[0] << " G: " << (int)pixel[1] << " B: " << (int)pixel[2] << std::endl;

                // Check what object is cursor over and do something
                for (GamePawn &itr : this->Pawn)
                {
                    if (itr.ColorID.r * 255.0f == pixel[0] && itr.ColorID.g * 255.0f == pixel[1] && itr.ColorID.b * 255.0f == pixel[2])
                    {
                        // Destroy pawn and add score
                        std::cout << "You get: " << itr.Score << " scores for clicking." << std::endl;
                        this->Score += itr.Score;
                        itr.isDestroyed = GL_TRUE;
                    }
                }
            }
        }
        else
        {

        }

        // Set that this key already processed
        this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT] = GL_TRUE;
    }
    if (this->Keys[GLFW_KEY_ESCAPE] && !this->Keysprocessed[GLFW_KEY_ESCAPE])
    {
        if (this->Currentlevel == PLAY_LV)
        {
            if (this->CurrentPlayState != PAUSE && this->CurrentPlayState != END)
            {
                this->CurrentPlayState = PAUSE;
            }
            else if (this->CurrentPlayState == PAUSE)
            {
                this->CurrentPlayState = PLAY;
            }
        }

        this->Keysprocessed[GLFW_KEY_ESCAPE] = GL_TRUE;
    }
}

GLvoid Game::DrawCurrentLevel(GLfloat dt)
{
    if (this->Currentlevel == PLAY_LV)
    {
        SpriteRenderer->Draw(ResourceManager::GetTexture("theme_background"), glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        for (GamePawn &itr : this->Pawn)
        {
            if (itr.isDestroyed) continue;
            itr.Draw(*SpriteRenderer);
        }

        static GLchar buffertext[32];
        sprintf(buffertext, "Score: %d", this->Score);
        TextRenderer->RenderText(buffertext, 0.0f, 0.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));

        sprintf(buffertext, "Time: %.2f", this->Time);
        TextRenderer->RenderText(buffertext, 0.0f, 50.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));

        if (this->Currentmode == ENDLESS)
        {
            sprintf(buffertext, "Lives: %d", this->Lives);
            TextRenderer->RenderText(buffertext, 0.0f, 100.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
        }

        if (this->CurrentPlayState == END)
        {
            TextRenderer->RenderText("GAME OVER... YOU LOSE TO MIMI!", (this->windowWidth / 2) - 312.0f, (this->windowHeight / 2) - 30.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
        }
    }
}

GLvoid Game::SpawnPawn(GLfloat dt)
{
    if (this->Currentmode == TIME_ATTACK)
    {
        static GLfloat PlayTimer = 0.0f;

        PlayTimer += dt;

        // Random spawn by time
        static GLfloat red = 1.0f; static GLfloat green = 0.0f; static GLfloat blue = 0.0f;
        static GLfloat TimeSpawnBase = 1.75f;
        static GLfloat NextTimeSpawn = 0.0f;
        if (PlayTimer > NextTimeSpawn)
        {
            for (GLfloat i = 0.0f; i < PlayTimer / 5; i++)
            {

                GLfloat x_pos = std::rand() % (this->windowWidth - 100 + 1);
                GLfloat y_pos = std::rand() % (this->windowHeight - 100 + 1);
                GLfloat percentofrarespawn = std::rand() % 10000;
                if (percentofrarespawn >= 0 && percentofrarespawn <= 6000)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 3, 1, glm::vec2(x_pos, y_pos), glm::vec2(100, 100), ResourceManager::GetTexture("theme_pawn1")));
                }
                else if (percentofrarespawn >= 6001 && percentofrarespawn <= 8500)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 2.5, 3, glm::vec2(x_pos, y_pos), glm::vec2(80, 80), ResourceManager::GetTexture("theme_pawn2")));
                }
                else if (percentofrarespawn >= 8501 && percentofrarespawn <= 9999)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 1.75, 5, glm::vec2(x_pos, y_pos), glm::vec2(60, 60), ResourceManager::GetTexture("theme_pawn3")));
                }
                if (red != 255)
                {
                    red++;
                }
                else if (green != 255)
                {
                    red = 1.0f;
                    green++;
                }
                else
                {
                    red = 1.0f;
                    green = 0.0f;
                    blue++;
                }
            }
            NextTimeSpawn += TimeSpawnBase;
        }
    }
    else if (this->Currentmode == ENDLESS)
    {
        static GLfloat PlayTimer = 0.0f;

        PlayTimer += dt;

        // Random spawn by time
        static GLfloat red = 1.0f; static GLfloat green = 0.0f; static GLfloat blue = 0.0f;
        static GLfloat TimeSpawnBase = 1.75f;
        static GLfloat NextTimeSpawn = 0.0f;
        if (PlayTimer > NextTimeSpawn)
        {
            for (GLfloat i = 0.0f; i < PlayTimer / 5; i++)
            {

                GLfloat x_pos = std::rand() % (this->windowWidth - 100 + 1);
                GLfloat y_pos = std::rand() % (this->windowHeight - 100 + 1);
                GLfloat percentofrarespawn = std::rand() % 10000;
                if (percentofrarespawn >= 0 && percentofrarespawn <= 6000)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 3, 1, glm::vec2(x_pos, y_pos), glm::vec2(100, 100), ResourceManager::GetTexture("theme_pawn1")));
                }
                else if (percentofrarespawn >= 6001 && percentofrarespawn <= 8500)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 2.5, 3, glm::vec2(x_pos, y_pos), glm::vec2(80, 80), ResourceManager::GetTexture("theme_pawn2")));
                }
                else if (percentofrarespawn >= 8501 && percentofrarespawn <= 9999)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 1.75, 5, glm::vec2(x_pos, y_pos), glm::vec2(60, 60), ResourceManager::GetTexture("theme_pawn3")));
                }
                if (red != 255)
                {
                    red++;
                }
                else if (green != 255)
                {
                    red = 1.0f;
                    green++;
                }
                else
                {
                    red = 1.0f;
                    green = 0.0f;
                    blue++;
                }
            }
            NextTimeSpawn += TimeSpawnBase;
        }
    }
}