//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "BearTrap.h"

BearTrap::BearTrap(ASGE::Renderer* renderer, int tile_size) :
  item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture(Frame1);
  spriteComponent->getSprite()->height(tile_size);
  spriteComponent->getSprite()->width(tile_size);
  item_id = 0;
}

void BearTrap::updateBearTrap(int tileSize, int frame)
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