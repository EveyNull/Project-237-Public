//
// Created by Kirsten on 15/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BOTTLE_H
#define THE_SHINING_GAME_PROJECT_237_BOTTLE_H

#include "item.h"

class Bottle : public item
{
 public:
  Bottle(ASGE::Renderer* renderer, int tile_size);
  void update(float delta_time);

 private:
  float timer = 0;
  float ogX = 0;
  float ogY = 0;
  std::string Frame1 = "/data/ui_images/bottleicon.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BOTTLE_H
