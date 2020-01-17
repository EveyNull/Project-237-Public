//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "BearTrap.h"

bool BearTrap::initialiseBearTrap(ASGE::Renderer* renderer,
                                  int tileSize,
                                  float xpos,
                                  float ypos)
{
  addSpriteComponent(renderer, Frame1, 50);
  getSpriteComponent()->getSprite()->xPos(xpos);
  getSpriteComponent()->getSprite()->yPos(ypos);
  setEnabled(true);
  getSpriteComponent()->setVisible(true);
  return (true);
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