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

void SpriteComponent::setVisible(bool vis)
{
  visible = vis;
}

bool SpriteComponent::getVisible()
{
  return visible;
}

rect SpriteComponent::getBoundingBox() const
{
  rect bounding_box;
  bounding_box.x = sprite->xPos();
  bounding_box.y = sprite->yPos();
  bounding_box.length = sprite->width();
  bounding_box.height = sprite->height();

  return bounding_box;
}