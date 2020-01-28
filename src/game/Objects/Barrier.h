//
// Created by Kirsten on 15/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BARRIER_H
#define THE_SHINING_GAME_PROJECT_237_BARRIER_H

#include "item.h"

class Barrier : public item
{
 public:
  Barrier(ASGE::Renderer* renderer, int tile_size);

 private:
  std::string Frame1 = "/data/item_images/fence.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BARRIER_H
