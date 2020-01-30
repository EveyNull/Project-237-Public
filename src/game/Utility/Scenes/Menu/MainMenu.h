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
                 const std::deque<bool>& keys_pressed,
                 const ASGE::ClickEvent& click_event,
                 Vector2 mouse_pos,
                 ASGE::Renderer*) override;

  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event,
                 Vector2 mouse_pos);

  void render(ASGE::Renderer* renderer, Vector2 window_size) override;

  void checkMouseOverOption(Vector2 mouse_pos);

 private:
  Vector2 window_size;
  std::vector<GameObject> menu_buttons;
  GameObject background;
  int num_buttons = 5;

  std::string menu_button_textures[5] = {
    "/data/menu_icons/EasyOff.png", "/data/menu_icons/MediumOff.png",
    "/data/menu_icons/HardOff.png", "/data/menu_icons/LoreOff.png",
    "/data/menu_icons/ExitOff.png",
  };

  std::string menu_button_textures_On[5] = {
    "/data/menu_icons/EasyOn.png", "/data/menu_icons/MediumOn.png",
    "/data/menu_icons/HardOn.png", "/data/menu_icons/LoreOn.png",
    "/data/menu_icons/ExitOn.png",
  };

  std::pair<int, int> texture_sizes[5] = {
    { 240, 50 }, { 240, 50 }, { 240, 50 }, { 240, 50 }, { 240, 50 },
  };

  float top_menu_text_ypos = 150.f;
};

#endif // THE_SHINING_GAME_PROJECT_237_MAINMENU_H
