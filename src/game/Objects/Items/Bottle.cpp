//
// Created by Kirsten on 15/01/2020.
//

#include "Bottle.h"

Bottle::Bottle(ASGE::Renderer* renderer, int tile_size) :
  Item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture(Frame1);
  // spriteComponent->getSprite()->xPos(spriteComponent->getSprite()->xPos() +
  // (tile_size/4));
  // spriteComponent->getSprite()->yPos(spriteComponent->getSprite()->yPos() +
  // (tile_size/4));
  spriteComponent->getSprite()->height(tile_size / 2);
  spriteComponent->getSprite()->width(tile_size / 2);
  item_id = BOTTLE;
}

void Bottle::update(int tile_size, int frame, float delta_time)
{
  timer += (delta_time / 1000);

  if (timer <= 0.5 || ((1 < timer) && (timer <= 1.5)))
  {
    // setXPos(ogX);
    setYPos(ogY);
  }

  if ((0.5 < timer) && (timer <= 1))
  {
    // setXPos(ogX + 10);
    setYPos(ogY + 5);
  }

  if ((1.5 < timer) && (timer <= 2))
  {
    // setXPos(ogX - 10);
    setYPos(ogY - 5);
  }

  if (timer > 2)
  {
    timer = 0;
  }
}