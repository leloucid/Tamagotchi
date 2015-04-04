#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
TextRender *TextRenderer;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(MENU_LV), Currenttheme(0), score(0)
{

}

Game::~Game()
{
    delete SpriteRenderer;
    delete TextRenderer;
}

GLvoid Game::init()
{
    // Load shaders
    ResourceManager::LoadShader("../Shader/sprite.vert", "../Shader/sprite.frag", "sprite");
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
    // Set render-specific controls
    SpriteRenderer = new SpriteRender(ResourceManager::GetShader("sprite"));
    TextRenderer = new TextRender(this->windowWidth, this->windowHeight);
    TextRenderer->Load("../Font/supermarket.ttf", 128);

    // Create GamePawn
    this->Pawn.push_back(GamePawn(8, 2, glm::vec2(35, 42), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(12, 3, glm::vec2(535, 352), glm::vec2(100, 100), ResourceManager::GetTexture("pawn3")));
    this->Pawn.push_back(GamePawn(7, 6, glm::vec2(145, 215), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(9, 5, glm::vec2(685, 231), glm::vec2(100, 100), ResourceManager::GetTexture("pawn3")));
    this->Pawn.push_back(GamePawn(3, 2, glm::vec2(456, 565), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(6, 4, glm::vec2(875, 555), glm::vec2(100, 100), ResourceManager::GetTexture("pawn2")));
}

GLvoid Game::Update(GLfloat dt)
{
    static GLfloat timer = 0.0f;

    timer += dt;
    printf("%.3f\n", timer);

    for (GamePawn &itr : this->Pawn)
    {
        if (itr.isDestroyed) continue;
        itr.aliveTime -= dt;
        if (itr.aliveTime <= 0) itr.isDestroyed = GL_TRUE;
    }
}

GLvoid Game::Render(GLfloat dt)
{
    SpriteRenderer->Draw(ResourceManager::GetTexture("menu_background") ,glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    for (GamePawn &itr : this->Pawn)
    {
        if (itr.isDestroyed) continue;
        itr.Draw(*SpriteRenderer);
    }

    TextRenderer->RenderText("Everyone love mimi <3", 250.0f, 200.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
}

GLvoid Game::ProcessInput()
{
    if (this->key[GLFW_MOUSE_BUTTON_LEFT] && !this->keyprocessed[GLFW_MOUSE_BUTTON_LEFT])
    {
        //check all object.onclick() (pawn, button, etc).
        this->keyprocessed[GLFW_MOUSE_BUTTON_LEFT] = GL_TRUE;
    }
    if (this->Currentlevel == PLAY_LV)
    {
        if (this->CurrentPlayState != PAUSE && this->CurrentPlayState != END)
        {
            if (this->key[GLFW_KEY_ESCAPE] && !this->keyprocessed[GLFW_KEY_ESCAPE])
            {
                //game pause
                this->keyprocessed[GLFW_KEY_ESCAPE] = GL_TRUE;
            }
        }
    }
}