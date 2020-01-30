//
// Created by e22-watson on 30/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_LOREPICKUP_H
#define THE_SHINING_GAME_PROJECT_237_LOREPICKUP_H

#include "../../Utility/UI/ItemIDs.h"
#include "item.h"

class LorePickup : public item
{
 public:
  LorePickup(ASGE::Renderer* renderer, int tile_size, int n_lore_index);
  int getLoreIndex();

 private:
  int lore_index;
};

#endif // THE_SHINING_GAME_PROJECT_237_LOREPICKUP_H
