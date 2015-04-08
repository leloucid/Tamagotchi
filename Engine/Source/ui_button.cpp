#include "ui_button.h"

UIButton::UIButton() : ColorID(glm::vec3(0.0f)), Position(0, 0), Size(1, 1), Color(1.0f), Rotation(0.0f), Sprite()
{

}

UIButton::UIButton(glm::vec3 colorID, glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color) : ColorID(colorID), Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite)
{

}

GLvoid UIButton::Draw(SpriteRender &renderer)
{
    renderer.Draw(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

GLvoid UIButton::DrawColorID(SpriteRender &renderer)
{
    glDisable(GL_DITHER);
    renderer.Draw(this->Sprite, this->Position, this->Size, this->Rotation, this->ColorID);
    glEnable(GL_DITHER);
}

GLvoid UIButton::OnClick(GLvoid (*fntpr)())
{
    this->fnptr = fntpr;
}