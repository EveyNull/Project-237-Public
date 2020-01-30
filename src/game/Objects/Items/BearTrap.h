//
// Created by k2-wotherspoon on 13/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BEARTRAP_H
#define THE_SHINING_GAME_PROJECT_237_BEARTRAP_H

<<<<<<< refs/remotes/origin/development:src/game/Objects/Items/BearTrap.h
#include "../../Utility/UI/ItemIDs.h"
#include "../GameObject.h"
#include "Item.h"
=======
#include "../Utility/ItemIDs.h"
#include "GameObject.h"
#include "item.h"
>>>>>>> Items - bottles work, UI fix, minor AI fix:src/game/Objects/BearTrap.h

class BearTrap : public Item
{
 public:
  BearTrap(ASGE::Renderer* renderer, int tile_size);

  void update(int tile_size, int frame, float delta_time) override;

 private:
  std::string Frame1 = "/data/item_images/bear1.png";
  std::string Frame2 = "/data/item_images/bear2.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_BEARTRAP_H
