//
// Created by e22-watson on 13/01/2020.
//

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(ASGE::Renderer* renderer,
                                 const std::string& sprite_file,
                                 float& tile_size)
{
  sprite = renderer->createRawSprite();
  sprite->loadTexture(sprite_file);
  sprite->width(tile_size);
  sprite->height(tile_size);
}

ASGE::Sprite* SpriteComponent::getSprite()
{
  return sprite;
}