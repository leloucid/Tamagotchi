#include "main.h"
#include "game.h"
#include "resourcemanager.h"
#include "spriterender.h"
#include "textrender.h"
//#include "sound.h"

SpriteRender *SpriteRenderer;
SpriteRender *ColorIDRenderer;
TextRender *TextRenderer;

static GLchar pathlist[255][64];
static GLint themecount = 0;
static GLchar temptheme[255][256];

GLvoid de_allocatethemepreview();

Game::Game(GLuint width, GLuint heigth) : windowWidth(width), windowHeight(heigth) ,Currentlevel(PLAY_LV)
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
    // UI BG
    ResourceManager::LoadTexture("../Images/milkyway-galaxy-bg.jpg", GL_FALSE, "background");
    // UI Button loaded
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
    this->ChangeLevel(PLAY_LV);
}

GLvoid Game::Update(GLfloat dt)
{
    
}

GLvoid Game::Render(GLfloat dt)
{
    DrawCurrentLevel(dt);
}

GLvoid Game::ProcessInput()
{
    if (this->Keys[GLFW_MOUSE_BUTTON_LEFT] && !this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT])
    {
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
                itr.isClicked = GL_FALSE;
                /* Button action : check button by color coding

                if (itr.ColorID.r * 255.0f == 1.0f && itr.ColorID.g * 255.0f == 0.0f && itr.ColorID.b * 255.0f == 0.0f)
                {
                    this->ChangeLevel(THEME_LV);
                }
                */
                break;
            }
        }
        
        // Set that this key already processed
        this->Keysprocessed[GLFW_MOUSE_BUTTON_LEFT] = GL_TRUE;
    }
    if (this->Keys[GLFW_KEY_ESCAPE] && !this->Keysprocessed[GLFW_KEY_ESCAPE])
    {
        // Escape action
        this->Keysprocessed[GLFW_KEY_ESCAPE] = GL_TRUE;
    }
}

GLvoid Game::DrawCurrentLevel(GLfloat dt)
{
    SpriteRenderer->Draw(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->windowWidth, this->windowHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

    for (UIButton &itr : this->Buttons)
    {
        itr.Draw(*SpriteRenderer);
    }
}

GLvoid Game::ChangeLevel(GameLevel level)
{
    this->Currentlevel = level;
}

GLvoid Game::ResetGame()
{

}

GLvoid Game::ResetColorID()
{
    this->RSCID_red = 1.0f;
    this->RSCID_green = 0.0f;
    this->RSCID_blue = 0.0f;
}