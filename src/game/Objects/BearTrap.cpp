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
  switch (frame)
  {
    case 1:
    {
      getSpriteComponent()->getSprite()->loadTexture(Frame1);
      break;
    }
    case 2:
    {
      getSpriteComponent()->getSprite()->loadTexture(Frame2);
      break;
    }
    default:
    {
      getSpriteComponent()->getSprite()->loadTexture(Frame1);
      break;
    }
  }

  getSpriteComponent()->getSprite()->height(tileSize);
  getSpriteComponent()->getSprite()->width(tileSize);
  getSpriteComponent()->getSprite()->xPos(getXPos());
  getSpriteComponent()->getSprite()->yPos(getYPos());
}