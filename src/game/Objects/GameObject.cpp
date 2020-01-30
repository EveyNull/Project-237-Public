//
// Created by e22-watson on 13/01/2020.
//

#include "GameObject.h"

bool GameObject::addSpriteComponent(ASGE::Renderer* renderer)
{
  if (!spriteComponent)
  {
    spriteComponent = new SpriteComponent(renderer);
  }
}
bool GameObject::addSpriteComponent(ASGE::Renderer* renderer,
                                    const std::string& sprite_file)
{
  if (!spriteComponent)
  {
    spriteComponent = new SpriteComponent(renderer, sprite_file);
  }
}

bool GameObject::addSpriteComponent(ASGE::Renderer* renderer,
                                    const std::string& sprite_file,
                                    float sprite_size)
{
  if (!spriteComponent)
  {
    spriteComponent = new SpriteComponent(renderer, sprite_file, sprite_size);
  }
}

SpriteComponent* GameObject::getSpriteComponent()
{
  if (spriteComponent)
  {
    return spriteComponent;
  }
  return nullptr;
}

float GameObject::getXPos()
{
  return position.getX();
}

float GameObject::getYPos()
{
  return position.getY();
}

Vector2 GameObject::getPos()
{
  return position;
}

void GameObject::setXPos(float new_xpos)
{
  position.setX(new_xpos);
}

void GameObject::setYPos(float new_ypos)
{
  position.setY(new_ypos);
}

void GameObject::setPos(Vector2 new_pos)
{
  position = new_pos;
}