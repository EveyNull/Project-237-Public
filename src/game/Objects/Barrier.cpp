//
// Created by Kirsten on 15/01/2020.
//

#include "Barrier.h"

Barrier::Barrier(ASGE::Renderer* renderer, int tile_size) :
  Item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture(Frame1);
  spriteComponent->getSprite()->height(tile_size);
  spriteComponent->getSprite()->width(tile_size);
  item_id = 3;
}

void Barrier::update(int tile_size, int frame, float delta_time) {}