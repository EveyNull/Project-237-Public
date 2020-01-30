//
// Created by e22-watson on 24/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_MAINMENU_H
#define THE_SHINING_GAME_PROJECT_237_MAINMENU_H

#include <Engine/Renderer.h>

#include "MenuOption.h"
#include "Scene.h"
#include "SceneID.h"

class MainMenu : public Scene
{
 public:
  explicit MainMenu(const Vector2& n_window_size);
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event,
                 ASGE::Renderer*);
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event) override;
  void render(ASGE::Renderer* renderer, Vector2 window_size) override;

  MenuOption checkClickedMenuOption(float xPos, float yPos);

 private:
  float top_menu_text_ypos = 100.f;
  Vector2 window_size;
};

#endif // THE_SHINING_GAME_PROJECT_237_MAINMENU_H
