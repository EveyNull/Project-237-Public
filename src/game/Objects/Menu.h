//
// Created by Joshua on 22/01/2020.
//

#pragma once

#include "GameObject.h";

#ifndef THE_SHINING_GAME_PROJECT_237_MENU_H
#  define THE_SHINING_GAME_PROJECT_237_MENU_H

class Menu
{
 public:
  ~Menu() = default;
  Menu(const Menu&) = default;
  Menu();

  void update();
  void render(ASGE::Renderer* renderer, Vector2 window_size);

 private:
  GameObject* title = nullptr;
  GameObject* play_game[2] = { nullptr, nullptr };
  GameObject* help_menu[2] = { nullptr, nullptr };
  GameObject* lore_menu[2] = { nullptr, nullptr };
  GameObject* exit_game[2] = { nullptr, nullptr };
};

#endif // THE_SHINING_GAME_PROJECT_237_MENU_H
