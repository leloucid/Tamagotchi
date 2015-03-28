#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
//#include "textrender.h"
//#include "sound.h"

SpriteRender *Renderer;
//TextRedner *text;

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(MAIN_MENU), Currenttheme(0), score(0)
{

}

Game::~Game()
{
    delete Renderer;
}

GLvoid Game::init()
{
    // Load shaders
    ResourceManager::LoadShader("../Shader/sprite.vert", "../Shader/sprite.frag", "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->windowWidth), static_cast<GLfloat>(this->windowHeight), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
    // Set render-specific controls
    Renderer = new SpriteRender(ResourceManager::GetShader("sprite"));
}

GLvoid Game::Render(GLfloat dt)
{
    Renderer->Draw(glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}