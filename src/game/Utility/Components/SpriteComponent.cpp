//
// Created by e22-watson on 13/01/2020.
//

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::unique_ptr<ASGE::Renderer>& renderer,
                                 const std::string& sprite_file)
{
  sprite = renderer->createRawSprite();
  sprite->loadTexture(sprite_file);
  sprite->xPos(0);
  sprite->yPos(0);
  sprite->width(10);
  sprite->height(10);
}

ASGE::Sprite* SpriteComponent::getSprite()
{
  return sprite;
}