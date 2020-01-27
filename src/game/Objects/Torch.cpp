//
// Created by Kirsten on 14/01/2020.
//

#include "Torch.h"

Torch::Torch(ASGE::Renderer* renderer, int tileSize, float xpos, float ypos)
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
  item_id = 4;
}

void Torch::updateTorch(int tile_size, float delta_time)
{
  timer += (delta_time / 1000);

  if (timer <= 0.5 || ((1 < timer) && (timer <= 1.5)))
  {
    setFrame(1);
    changeFrame(1);
  }

  if ((0.5 < timer) && (timer <= 1))
  {
    setFrame(2);
    changeFrame(2);
  }

  if ((1.5 < timer) && (timer <= 2))
  {
    setFrame(3);
    changeFrame(3);
  }

  if (timer > 2)
  {
    timer = 0;
  }

  getSpriteComponent()->getSprite()->height(tile_size);
  getSpriteComponent()->getSprite()->width(tile_size);
  getSpriteComponent()->getSprite()->xPos(getXPos());
  getSpriteComponent()->getSprite()->yPos(getYPos());
}

void Torch::changeFrame(int frame_number)
{
  switch (frame_number)
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
}