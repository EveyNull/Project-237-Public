//
// Created by Kirsten on 14/01/2020.
//

#include "Torch.h"

Torch::Torch(ASGE::Renderer* renderer, int tile_size) :
  Item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture(Frame1);
  spriteComponent->getSprite()->height(tile_size / 2);
  spriteComponent->getSprite()->width(tile_size / 2);
  item_id = TORCH;
}

void Torch::update(int tile_size, int frame, float delta_time)
{
  torch_timer += (delta_time / 1000);

  if (torch_timer <= 0.5 || ((1 < torch_timer) && (torch_timer <= 1.5)))
  {
    setFrame(1);
    changeFrame(1);
  }

  if ((0.5 < torch_timer) && (torch_timer <= 1))
  {
    setFrame(2);
    changeFrame(2);
  }

  if ((1.5 < torch_timer) && (torch_timer <= 2))
  {
    setFrame(3);
    changeFrame(3);
  }

  if (torch_timer > 2)
  {
    torch_timer = 0;
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