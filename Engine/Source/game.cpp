#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
TextRender *TextRenderer;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(MAIN_MENU), Currenttheme(0), score(0)
{

}

Game::~Game()
{
    delete SpriteRenderer;
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
}

GLvoid Game::Render(GLfloat dt)
{
    SpriteRenderer->Draw(ResourceManager::GetTexture("menu_background") ,glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("pawn1") ,glm::vec2(35, 42), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("pawn3"), glm::vec2(535, 352), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("pawn1"), glm::vec2(145, 215), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("orange"), glm::vec2(((this->windowWidth / 2) - 50), ((this->windowHeight / 2) - 50)), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("pawn3"), glm::vec2(685, 231), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("pawn2"), glm::vec2(456, 565), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    SpriteRenderer->Draw(ResourceManager::GetTexture("pawn2"), glm::vec2(875, 555), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    TextRenderer->RenderText("Everyone love mimi <3", 250.0f, 200.0f, 0.40f, glm::vec3(255.0f / 255.0f, 28.0f / 255.0f, 202.0f / 255.0f));
}