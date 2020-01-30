//
// Created by Kirsten on 16/01/2020.
//

#include <deque>

#include "../../Objects/GameObject.h"
#include "Inventory.h"

#ifndef THE_SHINING_GAME_PROJECT_237_UI_H
#  define THE_SHINING_GAME_PROJECT_237_UI_H

class UI
{
 public:
  UI(const UI&) = default;
  void initialiseUI(ASGE::Renderer* renderer);
  void render(ASGE::Renderer* renderer);
  explicit UI(ASGE::Renderer* renderer);
  void update(int slot, int itemID, int number);
  void changeSlot(int new_slot);
  void fillBar(float xpos, float ypos, float timer);
  void stopFill();

 private:
  int total_slots = 9;
  float fill_amount = 0;

  float UI_size = 50;

  //  Inventory* test = nullptr;

  int itemArray[9][2];

  GameObject selecter;
  GameObject slots[9];

  GameObject fill_bar;
  GameObject filler;

  GameObject bear_trap;
  GameObject torch;
  GameObject bottle;
  GameObject barrier;

  std::string selecter_sprite = "data/ui_images/select.png";
  std::string slot_sprite = "data/ui_images/ui_itembox.png";
  std::string fill_bar_sprite = "data/ui_images/fill_bar.png";
  std::string filler_sprite = "data/1px.png";

  std::string bear_trap_sprite = "data/ui_images/bearicon.png";
  std::string torch_sprite = "data/item_images/torchOn1.png";
  std::string bottle_sprite = "data/ui_images/bottleicon.png";
  std::string barrier_sprite = "data/item_images/fence.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_UI_H
