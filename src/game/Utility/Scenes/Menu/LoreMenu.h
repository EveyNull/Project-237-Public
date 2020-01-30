//
// Created by c2-worden on 27/01/2020.
//
#include "../../../Objects/GameObject.h"
#include "../../Static Classes/DataManager.h"
#include "../../Vector2.h"
#include "../Scene.h"
#include "LoreOption.h"
#include <Engine/OGLGame.h>
#include <deque>

#ifndef THE_SHINING_GAME_PROJECT_237_LOREMENU_H
#  define THE_SHINING_GAME_PROJECT_237_LOREMENU_H

class LoreMenu : public Scene
{
 public:
  explicit LoreMenu(const Vector2& n_window_size, ASGE::Renderer* renderer);
  ~LoreMenu() = default;
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event,
                 Vector2 mouse_pos);
  SceneID update(float delta_time,
                 const std::deque<bool>& keys_held,
                 const std::deque<bool>& keys_released,
                 const ASGE::ClickEvent& click_event,
                 Vector2 mouse_pos,
                 ASGE::Renderer*) override;

  void render(ASGE::Renderer* renderer, Vector2 window_size) override;

  LoreOption checkClickedLore(float xPos, float yPos);

  void loadLore(ASGE::Renderer* renderer, const Vector2& window_size);
  void renderLore();

 private:
  bool lore_opened = false;
  bool locked = true;

  float top_text_Ypos = 100.f;

  std::vector<bool> unlocked_lore;
  std::vector<GameObject> lore_buttons;
  GameObject* lore_list[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
  Vector2 window_size;
  LoreOption lore_selected = NO_LORE;

  std::string lore_button_textures[5] = { "/data/menu_icons/Lore1Locked.png",
                                          "/data/menu_icons/Lore2Locked.png",
                                          "/data/menu_icons/Lore3Locked.png",
                                          "/data/menu_icons/Lore4Locked.png",
                                          "/data/menu_icons/Lore5Locked.png" };

  std::string lore_button_textures_off[6] = {
    "/data/menu_icons/Lore1Off.png", "/data/menu_icons/Lore2Off.png",
    "/data/menu_icons/Lore3Off.png", "/data/menu_icons/Lore4Off.png",
    "/data/menu_icons/Lore5Off.png", "/data/menu_icons/MainMenuOff.png"
  };

  std::string lore_button_textures_On[6] = {
    "/data/menu_icons/Lore1On.png", "/data/menu_icons/Lore2On.png",
    "/data/menu_icons/Lore2On.png", "/data/menu_icons/Lore4On.png",
    "/data/menu_icons/Lore4On.png", "/data/menu_icons/MainMenuOn.png"
  };
};

#endif // THE_SHINING_GAME_PROJECT_237_LOREMENU_H
