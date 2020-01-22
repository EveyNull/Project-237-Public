//
// Created by Kirsten on 14/01/2020.
//

#include "Torch.h"

void Torch::initialiseTorch(ASGE::Renderer* renderer,
                            int tileSize,
                            float xpos,
                            float ypos)
{
  addSpriteComponent(renderer, Frame1, tileSize);
  setXPos(xpos);
  setYPos(ypos);
  getSpriteComponent()->getSprite()->height(tileSize);
  getSpriteComponent()->getSprite()->width(tileSize);
  getSpriteComponent()->getSprite()->xPos(xpos);
  getSpriteComponent()->getSprite()->yPos(ypos);
  setEnabled(true);
  getSpriteComponent()->setVisible(true);
}

void Torch::updateTorch(int tileSize)
{
  int whichFrame = getFrame();

  switch (whichFrame)
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
    case 3:
    {
      getSpriteComponent()->getSprite()->loadTexture(Frame3);
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