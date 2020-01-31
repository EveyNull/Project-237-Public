//
// Created by Kirsten on 15/01/2020.
//

#include "Barrier.h"

Barrier::Barrier(ASGE::Renderer* renderer, int tile_size) :
  Item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture(Frame2);
  spriteComponent->getSprite()->height(tile_size);
  spriteComponent->getSprite()->width(tile_size);
  item_id = BARRIER;
}

void Barrier::updateTimer(float delta_time, int tile_size)
{
  if (enabled)
  {
    barrier_timer += (delta_time / 1000);
    if (barrier_timer > 10)
    {
      enabled = false;
      getSpriteComponent()->getSprite()->loadTexture(Frame2);
      spriteComponent->getSprite()->height(tile_size);
      spriteComponent->getSprite()->width(tile_size);
    }
  }
}

void Barrier::update(int tile_size, int frame, float delta_time)
{
  if (frame == 1)
  {
    getSpriteComponent()->getSprite()->loadTexture(Frame1);
    spriteComponent->getSprite()->height(tile_size);
    spriteComponent->getSprite()->width(tile_size);
  }
}