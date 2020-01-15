//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "BearTrap.h"

void BearTrap::initialiseBearTrap(std::unique_ptr<ASGE::Renderer>& renderer,
                                  int tileSize,
                                  float xpos,
                                  float ypos)
{
  addSpriteComponent(renderer, Frame1);
  getSprite()->height(tileSize);
  getSprite()->width(tileSize);
  getSprite()->xPos(xpos);
  getSprite()->yPos(ypos);
  setEnabled(true);
  setVisible(true);
}

void BearTrap::updateBearTrap(int tileSize)
{
  int whichFrame = getFrame();

  switch (whichFrame)
  {
    case 1:
    {
      getSprite()->loadTexture(Frame1);
      break;
    }
    case 2:
    {
      getSprite()->loadTexture(Frame2);
      break;
    }
    default:
    {
      getSprite()->loadTexture(Frame1);
      break;
    }
  }

  getSprite()->height(tileSize);
  getSprite()->width(tileSize);
  getSprite()->xPos(getXPos());
  getSprite()->yPos(getYPos());
}