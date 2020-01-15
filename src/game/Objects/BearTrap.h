//
// Created by k2-wotherspoon on 13/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BEARTRAP_H
#define THE_SHINING_GAME_PROJECT_237_BEARTRAP_H

#include "GameObject.h"
#include "item.h"

class BearTrap : public item
{
 public:
  void initialiseBearTrap(std::unique_ptr<ASGE::Renderer>& renderer,
                          int tileSize,
                          float xpos,
                          float ypos);

  void updateBearTrap(int tileSize);

 private:
  std::string Frame1 = "/data/item_images/bear1.png";
  std::string Frame2 = "/data/item_images/bear2.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BEARTRAP_H
