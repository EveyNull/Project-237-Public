//
// Created by Kirsten on 15/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BOTTLE_H
#define THE_SHINING_GAME_PROJECT_237_BOTTLE_H

<<<<<<< refs/remotes/origin/development:src/game/Objects/Items/Bottle.h
#include "../../Utility/UI/ItemIDs.h"
#include "Item.h"
=======
#include "../Utility/ItemIDs.h"
#include "item.h"
>>>>>>> Items - bottles work, UI fix, minor AI fix:src/game/Objects/Bottle.h

class Bottle : public Item
{
 public:
  Bottle(ASGE::Renderer* renderer, int tile_size);
  void update(int tile_size, int frame, float delta_time) override;

 private:
  float timer = 0;
  float ogX = 0;
  float ogY = 0;
  std::string Frame1 = "/data/ui_images/bottleicon.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BOTTLE_H
