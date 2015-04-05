#include "main.h"
#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
SpriteRender *ColorIDRenderer;
TextRender *TextRenderer;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(MENU_LV), Currenttheme(0), score(0)
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
    this->Pawn.push_back(GamePawn(glm::vec3(1.0 / 255.0f, 0, 0), 99, 2, glm::vec2(35, 42), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(glm::vec3(2.0 / 255.0f, 0, 0), 99, 3, glm::vec2(535, 352), glm::vec2(100, 100), ResourceManager::GetTexture("pawn3")));
    this->Pawn.push_back(GamePawn(glm::vec3(3.0 / 255.0f, 0, 0), 99, 6, glm::vec2(145, 215), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(glm::vec3(4.0 / 255.0f, 0, 0), 99, 5, glm::vec2(685, 231), glm::vec2(100, 100), ResourceManager::GetTexture("pawn3")));
    this->Pawn.push_back(GamePawn(glm::vec3(5.0 / 255.0f, 0, 0), 99, 2, glm::vec2(456, 565), glm::vec2(100, 100), ResourceManager::GetTexture("pawn1")));
    this->Pawn.push_back(GamePawn(glm::vec3(6.0 / 255.0f, 0, 0), 99, 4, glm::vec2(875, 555), glm::vec2(100, 100), ResourceManager::GetTexture("pawn2")));
}

GLvoid Game::Update(GLfloat dt)
{
    static GLfloat timer = 0.0f;

    timer += dt;
    //printf("%.3f\n", timer);

    for (GamePawn &itr : this->Pawn)
    {
        if (itr.isDestroyed) continue;
        itr.aliveTime -= dt;
        if (itr.aliveTime <= 0) itr.isDestroyed = GL_TRUE;
    }
}

GLvoid Game::Render(GLfloat dt)
{
    SpriteRenderer->Draw(ResourceManager::GetTexture("menu_background"), glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    for (GamePawn &itr : this->Pawn)
    {
        if (itr.isDestroyed) continue;
        itr.Draw(*SpriteRenderer);
    }

    TextRenderer->RenderText("Everyone love mimi <3", 250.0f, 200.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
}

GLvoid Game::ProcessInput()
{
    if (this->Keys[GLFW_MOUSE_BUTTON_LEFT] && !this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT])
    {
        //check all object.onclick() (pawn, button, etc).
        for (GamePawn &itr : this->Pawn)
        {
            if (itr.isDestroyed) continue;
            itr.DrawColorID(*ColorIDRenderer);
        }
        GLint viewport[4];
        GLubyte pixel[3];
        GLdouble xpos, ypos;
        glGetIntegerv(GL_VIEWPORT, viewport);
        glfwGetCursorPos(Getwindow(), &xpos, &ypos);
        glReadPixels(xpos, viewport[3]-ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void*)pixel);
        std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
        std::cout << "R: " << (int)pixel[0] << " G: " << (int)pixel[1] << " B: " << (int)pixel[2] << std::endl;
        this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT] = GL_TRUE;
    }
    if (this->Currentlevel == PLAY_LV)
    {
        if (this->CurrentPlayState != PAUSE && this->CurrentPlayState != END)
        {
            if (this->Keys[GLFW_KEY_ESCAPE] && !this->Keysprocessed[GLFW_KEY_ESCAPE])
            {
                //game pause
                this->Keysprocessed[GLFW_KEY_ESCAPE] = GL_TRUE;
            }
        }
    }
}