//
// Created by k2-wotherspoon on 13/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BEARTRAP_H
#define THE_SHINING_GAME_PROJECT_237_BEARTRAP_H

#include "../GameObject.h"
#include "item.h"

class BearTrap : public item
{
 public:
  BearTrap(ASGE::Renderer* renderer, int tile_size);

  void updateBearTrap(int tileSize, int frame);

 private:
  std::string Frame1 = "/data/item_images/bear1.png";
  std::string Frame2 = "/data/item_images/bear2.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BEARTRAP_H
