#include "main.h"
#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
SpriteRender *ColorIDRenderer;
TextRender *TextRenderer;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(PLAY_LV), Currenttheme(0), score(0)
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
    ResourceManager::LoadTexture("../Images/milkyway-galaxy-bg.jpg", GL_FALSE, "menu_background");
    ResourceManager::LoadTexture("../Images/container.jpg", GL_FALSE, "container");
    ResourceManager::LoadTexture("../Images/mimi1.png", GL_TRUE, "pawn1");
    ResourceManager::LoadTexture("../Images/mimi2.png", GL_TRUE, "pawn2");
    ResourceManager::LoadTexture("../Images/mimi3.png", GL_TRUE, "pawn3");
    ResourceManager::LoadTexture("../Images/orange_detoure.png", GL_TRUE, "orange");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->windowWidth), static_cast<GLfloat>(this->windowHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("colorid").Use().SetMatrix4("projection", projection);
    // Set render-specific controls
    SpriteRenderer = new SpriteRender(ResourceManager::GetShader("sprite"));
    ColorIDRenderer = new SpriteRender(ResourceManager::GetShader("colorid"));
    TextRenderer = new TextRender(this->windowWidth, this->windowHeight);
    TextRenderer->Load("../Font/supermarket.ttf", 128);

    // Create GamePawn
    /*
    this->Pawn.push_back(GamePawn(glm::vec3(2.0 / 255.0f, 0, 0), 9999, 3, glm::vec2(535, 352), glm::vec2(100, 100), ResourceManager::GetTexture("pawn3")));
    this->Pawn.push_back(GamePawn(glm::vec3(3.0 / 255.0f, 0, 0), 9999, 6, glm::vec2(145, 215), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(glm::vec3(4.0 / 255.0f, 0, 0), 9999, 5, glm::vec2(685, 231), glm::vec2(100, 100), ResourceManager::GetTexture("pawn3")));
    this->Pawn.push_back(GamePawn(glm::vec3(5.0 / 255.0f, 0, 0), 9999, 2, glm::vec2(456, 565), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(glm::vec3(6.0 / 255.0f, 0, 0), 9999, 4, glm::vec2(875, 555), glm::vec2(100, 100), ResourceManager::GetTexture("pawn2")));
    */
}

GLvoid Game::Update(GLfloat dt)
{
    if (this->Currentlevel = PLAY_LV)
    {
        static GLfloat PlayTimer = 0.0f;

        PlayTimer += dt;
        //printf("%.3f\n", PlayTimer);

        //if (this->CurrentPlayState = PLAY)
        //{
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
                        this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 3, 1, glm::vec2(x_pos, y_pos), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
                    }
                    else if (percentofrarespawn >= 6001 && percentofrarespawn <= 8500)
                    {
                        this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 2.5, 3, glm::vec2(x_pos, y_pos), glm::vec2(80, 80), ResourceManager::GetTexture("pawn2")));
                    }
                    else if (percentofrarespawn >= 8501 && percentofrarespawn <= 9999)
                    {
                        this->Pawn.push_back(GamePawn(glm::vec3(red / 255.0f, green / 255.0f, blue / 255.0f), 1.75, 5, glm::vec2(x_pos, y_pos), glm::vec2(60, 60), ResourceManager::GetTexture("pawn3")));
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
            // Reduce life time
            for (GamePawn &itr : this->Pawn)
            {
                if (itr.isDestroyed) continue;
                itr.aliveTime -= dt;
                if (itr.aliveTime <= 0) itr.isDestroyed = GL_TRUE;
            }
        //}
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
            glReadPixels(xpos, viewport[3]-ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void*)pixel);
            std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
            std::cout << "R: " << (int)pixel[0] << " G: " << (int)pixel[1] << " B: " << (int)pixel[2] << std::endl;

            // Check what object is cursor over and do something
            for (GamePawn &itr : this->Pawn)
            {
                if (itr.ColorID.r * 255.0f == pixel[0] && itr.ColorID.g * 255.0f == pixel[1] && itr.ColorID.b * 255.0f == pixel[2])
                {
                    // Destroy pawn and add score
                    std::cout << "You get: " << itr.Score << " scores for clicking." << std::endl;
                    itr.isDestroyed = GL_TRUE;
                }
            }

            // Set that this key already processed
            this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT] = GL_TRUE;
        }
        else
        {

        }
    }
    if (this->Keys[GLFW_KEY_ESCAPE] && !this->Keysprocessed[GLFW_KEY_ESCAPE])
    {
        if (this->Currentlevel == PLAY_LV)
        {
            if (this->CurrentPlayState != PAUSE && this->CurrentPlayState != END)
            {
                //game pause
                this->Keysprocessed[GLFW_KEY_ESCAPE] = GL_TRUE;
            }
            else if (this->CurrentPlayState == PAUSE)
            {
                //game unpause
                this->Keysprocessed[GLFW_KEY_ESCAPE] = GL_TRUE;
            }
        }
    }
}

GLvoid Game::DrawCurrentLevel(GLfloat dt)
{
    if (this->Currentlevel == PLAY_LV)
    {
        SpriteRenderer->Draw(ResourceManager::GetTexture("menu_background"), glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        for (GamePawn &itr : this->Pawn)
        {
            if (itr.isDestroyed) continue;
            itr.Draw(*SpriteRenderer);
        }

        TextRenderer->RenderText("Everyone love mimi <3", 250.0f, 200.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
    }
}