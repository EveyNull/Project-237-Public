//
// Created by Kirsten on 16/01/2020.
//

#include <deque>

#include "../Objects/GameObject.h"

#ifndef THE_SHINING_GAME_PROJECT_237_UI_H
#  define THE_SHINING_GAME_PROJECT_237_UI_H

class UI
{
 public:
  void initialiseUI(ASGE::Renderer* renderer);
  void render(ASGE::Renderer* renderer);
  explicit UI(ASGE::Renderer* renderer);
  void update(const std::deque<bool>& keys_pressed);

 private:
  int total_slots = 3;
  float fill_amount = 0;

  GameObject selecter;
  GameObject slots[3];

  GameObject bear_trap;
  GameObject torch;
  GameObject bottle;

  GameObject fill_bar;
  GameObject filler;

  std::string selecter_sprite = "data/ui_images/select.png";
  std::string slot_sprite = "data/ui_images/ui_itembox.png";
  std::string fill_bar_sprite = "data/ui_images/fill_bar.png";
  std::string filler_sprite = "data/1px.png";

  std::string bear_trap_sprite = "data/ui_images/bearicon.png";
  std::string torch_sprite = "data/item_images/attack_pea.png";
  std::string bottle_sprite = "data/ui_images/bottleicon.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_UI_H
