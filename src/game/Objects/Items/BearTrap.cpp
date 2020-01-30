//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "BearTrap.h"

BearTrap::BearTrap(ASGE::Renderer* renderer, int tile_size) :
  Item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture(Frame2);
  spriteComponent->getSprite()->height(tile_size);
  spriteComponent->getSprite()->width(tile_size);
  item_id = BEARTRAP;
}

void BearTrap::update(int tileSize, int frame, float delta_time)
{
  if (frame == 1)
  {
    getSpriteComponent()->getSprite()->loadTexture(Frame1);
  }
  if (frame == 2)
  {
    getSpriteComponent()->getSprite()->loadTexture(Frame2);
  }

  getSpriteComponent()->getSprite()->height(tileSize);
  getSpriteComponent()->getSprite()->width(tileSize);
  getSpriteComponent()->getSprite()->xPos(getXPos());
  getSpriteComponent()->getSprite()->yPos(getYPos());
}