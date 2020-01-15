//
// Created by Kirsten on 14/01/2020.
//

#include "Torch.h"

void Torch::initialiseTorch(std::unique_ptr<ASGE::Renderer>& renderer,
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

void Torch::updateTorch(int tileSize)
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
    case 3:
    {
      getSprite()->loadTexture(Frame3);
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