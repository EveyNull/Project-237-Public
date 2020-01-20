//
// Created by Kirsten on 19/01/2020.
//

#include <deque>

#ifndef THE_SHINING_GAME_PROJECT_237_PLAYER_H
#  define THE_SHINING_GAME_PROJECT_237_PLAYER_H

#  include "../Utility/Inventory.h"
#  include "../Utility/UI.h"
#  include "GameObject.h"
#  include "Projectile.h"

class Player : public GameObject
{
 public:
  ~Player() = default;
  Player(ASGE::Renderer* renderer, float new_tile_size);

  void update(const std::deque<bool>& keys_pressed, float delta_time);

  void pressUse();

  void pickUpItem();
  void placeItem();
  void useItem();

  void setInvSlot(int slot);
  int getInvSlot();

  void renderUI(ASGE::Renderer* renderer);

  Projectile* thrown_bottle = nullptr;

 private:
  Inventory* inventory = nullptr;
  UI* ui = nullptr;
  float currentX = 0;
  float currentY = 0;

  int inv_slot = 0;

  float tile_size = 0;

  float timer = 0;

  bool throwing = false;
  bool getting = false;
  bool putting = false;
  bool delaying = true;
};

#endif // THE_SHINING_GAME_PROJECT_237_PLAYER_H
