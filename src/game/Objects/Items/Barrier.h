//
// Created by Kirsten on 15/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BARRIER_H
#define THE_SHINING_GAME_PROJECT_237_BARRIER_H

#include "item.h"

class Barrier : public Item
{
 public:
  Barrier(ASGE::Renderer* renderer, int tile_size);
  void update(int tile_size, int frame, float delta_time) override;

 private:
  std::string Frame1 = "/data/item_images/fence.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BARRIER_H
