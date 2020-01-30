//
// Created by e22-watson on 24/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_MAINMENU_H
#define THE_SHINING_GAME_PROJECT_237_MAINMENU_H

#include <Engine/Renderer.h>
#include <vector>

#include "../../../Objects/GameObject.h"
#include "../Scene.h"
#include "../SceneID.h"
#include "MenuOption.h"

class MainMenu : public Scene
{
 public:
  explicit MainMenu(ASGE::Renderer* renderer, const Vector2& n_window_size);
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event,
                 ASGE::Renderer*);
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event,
                 ASGE::Renderer*);
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event) override;

  MenuOption checkClickedMenuOption(float xPos, float yPos);

  void render(ASGE::Renderer* renderer, Vector2 window_size) override;

 private:
  Vector2 window_size;
  std::vector<GameObject> menu_buttons;
  int num_buttons = 5;

  std::string menu_button_textures[5] = {
    "/data/menu_icons/play1.png", "/data/menu_icons/play1.png",
    "/data/menu_icons/play1.png", "/data/menu_icons/lore1.png",
    "/data/menu_icons/exit1.png",
  };

  std::pair<int, int> texture_sizes[5] = {
    { 72, 43 }, { 72, 43 }, { 72, 43 }, { 70, 34 }, { 70, 34 },
  };

  float top_menu_text_ypos = 150.f;
};

#endif // THE_SHINING_GAME_PROJECT_237_MAINMENU_H
