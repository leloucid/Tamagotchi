#include "main.h"
#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
SpriteRender *ColorIDRenderer;
TextRender *TextRenderer;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(MENU_LV), Currenttheme(0), Score(0)
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
    // UI Button loaded
    ResourceManager::LoadTexture("../Images/Button/btn_play.png", GL_TRUE, "ui_btn_play");
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
    // Initialize level
    this->ChangeLevel(MENU_LV);
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
            // Render the color ID
            for (UIButton &itr : this->Buttons)
            {
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
            for (UIButton &itr : this->Buttons)
            {
                if (itr.ColorID.r * 255.0f == pixel[0] && itr.ColorID.g * 255.0f == pixel[1] && itr.ColorID.b * 255.0f == pixel[2])
                {
                    // set isClicked to true to used to process in future
                    itr.isClicked = GL_TRUE;
                }
            }

            for (UIButton &itr : this->Buttons)
            {
                if (itr.isClicked)
                {
                    if (itr.ColorID.r * 255.0f == 1.0f, itr.ColorID.g * 255.0f == 0.0f, itr.ColorID.b * 255.0f == 0.0f)
                    {
                        itr.isClicked = GL_FALSE;
                        this->ChangeLevel(PLAY_LV);
                        this->Currentmode = TIME_ATTACK;
                        if (this->Currentmode == TIME_ATTACK) this->Time = 30.0f;
                        else if (this->Currentmode == ENDLESS) this->Lives = 15;
                        break;
                    }
                    
                }
            }
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
    if (this->Currentlevel == PLAY_LV)
    {
        if (this->CurrentPlayState == END)
        {
            GLint anykeypress;
            for (anykeypress = 10; anykeypress < 1024; anykeypress++)
            {
                if (this->Keys[anykeypress])
                {
                    this->ResetGame();
                    this->ChangeLevel(MENU_LV);
                    this->Keysprocessed[anykeypress] = GL_TRUE;
                    break;
                }
            }
        }
    }
}

GLvoid Game::DrawCurrentLevel(GLfloat dt)
{
    if (this->Currentlevel == MENU_LV)
    {
        SpriteRenderer->Draw(ResourceManager::GetTexture("theme_background"), glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        for (UIButton &itr : this->Buttons)
        {
            itr.Draw(*SpriteRenderer);
        }

    }
    else if (this->Currentlevel == PLAY_LV)
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

        if (this->CurrentPlayState == PAUSE)
        {
            TextRenderer->RenderText("GAME PAUSE!, Press ESC to continue", (this->windowWidth / 2) - 342.0f, (this->windowHeight / 2) - 30.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
        }

        if (this->CurrentPlayState == END)
        {
            TextRenderer->RenderText("GAME OVER... Press any key to start new game.", (this->windowWidth / 2) - 312.0f, (this->windowHeight / 2) - 30.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
        }
    }
}

GLvoid Game::SpawnPawn(GLfloat dt)
{
    if (this->Currentmode == TIME_ATTACK)
    {
        this->PlayTimer += dt;

        // Random spawn by time
        if (this->PlayTimer > this->NextTimeSpawn)
        {
            for (GLfloat i = 0.0f; i < PlayTimer / 5; i++)
            {
                GLfloat x_pos = std::rand() % (this->windowWidth - 100 + 1);
                GLfloat y_pos = std::rand() % (this->windowHeight - 100 + 1);
                GLfloat percentofrarespawn = std::rand() % 10000;
                if (percentofrarespawn >= 0 && percentofrarespawn <= 6000)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(this->RSCID_red / 255.0f, this->RSCID_green / 255.0f, this->RSCID_blue / 255.0f), 3, 1, glm::vec2(x_pos, y_pos), glm::vec2(100, 100), ResourceManager::GetTexture("theme_pawn1")));
                }
                else if (percentofrarespawn >= 6001 && percentofrarespawn <= 8500)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(this->RSCID_red / 255.0f, this->RSCID_green / 255.0f, this->RSCID_blue / 255.0f), 2.5, 3, glm::vec2(x_pos, y_pos), glm::vec2(80, 80), ResourceManager::GetTexture("theme_pawn2")));
                }
                else if (percentofrarespawn >= 8501 && percentofrarespawn <= 9999)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(this->RSCID_red / 255.0f, this->RSCID_green / 255.0f, this->RSCID_blue / 255.0f), 1.75, 5, glm::vec2(x_pos, y_pos), glm::vec2(60, 60), ResourceManager::GetTexture("theme_pawn3")));
                }
                if (this->RSCID_red != 255)
                {
                    this->RSCID_red++;
                }
                else if (this->RSCID_green != 255)
                {
                    this->RSCID_red = 1.0f;
                    this->RSCID_green++;
                }
                else
                {
                    this->RSCID_red = 1.0f;
                    this->RSCID_green = 0.0f;
                    this->RSCID_blue++;
                }
            }
            this->NextTimeSpawn += this->TimeSpawnBase;
        }
    }
    else if (this->Currentmode == ENDLESS)
    {
        this->PlayTimer += dt;

        // Random spawn by time
        if (this->PlayTimer > this->NextTimeSpawn)
        {
            for (GLfloat i = 0.0f; i < PlayTimer / 5; i++)
            {
                GLfloat x_pos = std::rand() % (this->windowWidth - 100 + 1);
                GLfloat y_pos = std::rand() % (this->windowHeight - 100 + 1);
                GLfloat percentofrarespawn = std::rand() % 10000;
                if (percentofrarespawn >= 0 && percentofrarespawn <= 6000)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(this->RSCID_red / 255.0f, this->RSCID_green / 255.0f, this->RSCID_blue / 255.0f), 3, 1, glm::vec2(x_pos, y_pos), glm::vec2(100, 100), ResourceManager::GetTexture("theme_pawn1")));
                }
                else if (percentofrarespawn >= 6001 && percentofrarespawn <= 8500)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(this->RSCID_red / 255.0f, this->RSCID_green / 255.0f, this->RSCID_blue / 255.0f), 2.5, 3, glm::vec2(x_pos, y_pos), glm::vec2(80, 80), ResourceManager::GetTexture("theme_pawn2")));
                }
                else if (percentofrarespawn >= 8501 && percentofrarespawn <= 9999)
                {
                    this->Pawn.push_back(GamePawn(glm::vec3(this->RSCID_red / 255.0f, this->RSCID_green / 255.0f, this->RSCID_blue / 255.0f), 1.75, 5, glm::vec2(x_pos, y_pos), glm::vec2(60, 60), ResourceManager::GetTexture("theme_pawn3")));
                }
                if (this->RSCID_red != 255)
                {
                    this->RSCID_red++;
                }
                else if (this->RSCID_green != 255)
                {
                    this->RSCID_red = 1.0f;
                    this->RSCID_green++;
                }
                else
                {
                    this->RSCID_red = 1.0f;
                    this->RSCID_green = 0.0f;
                    this->RSCID_blue++;
                }
            }
            this->NextTimeSpawn += this->TimeSpawnBase;
        }
    }
}

GLvoid Game::ChangeLevel(GameLevel level)
{
    this->Buttons.clear();
    this->ResetColorID();

    if (level == MENU_LV)
    {
        this->Currentlevel = MENU_LV;

        this->Buttons.push_back(UIButton(glm::vec3(1.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f), glm::vec2(0, 0), glm::vec2(250, 88), ResourceManager::GetTexture("ui_btn_play")));
    }
    else if (level == PLAY_LV)
    {
        this->Currentlevel = PLAY_LV;
        this->CurrentPlayState = PLAY;
    }
}

GLvoid Game::ResetGame()
{
    this->Score = 0;
    this->Time = 30.0f;
    this->Lives = 0;
    this->Pawn.clear();
    this->CurrentPlayState = PLAY;
    this->PlayTimer = 0.0f;
    this->NextTimeSpawn = 0.0f;
    this->ResetColorID();
}

GLvoid Game::ResetColorID()
{
    this->RSCID_red = 1.0f;
    this->RSCID_green = 0.0f;
    this->RSCID_blue = 0.0f;
}