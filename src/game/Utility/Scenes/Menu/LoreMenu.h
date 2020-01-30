//
// Created by c2-worden on 27/01/2020.
//

#include "../../../Objects/GameObject.h"
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
                 const ASGE::ClickEvent& click_event) override;

  void render(ASGE::Renderer* renderer, Vector2 window_size) override;

  LoreOption checkClickedLore(float xPos, float yPos);

  void loadLore(ASGE::Renderer* renderer, const Vector2& window_size);
  void renderLore();

  /* bool getLocked();
   void setLocked();
 */

 private:
  bool lore_opened = false;
  bool locked = true;

  float top_text_Ypos = 100.f;

  std::vector<GameObject> lore_buttons;
  GameObject* lore_list[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
  Vector2 window_size;
  LoreOption lore_selected = NO_LORE;
};

#endif // THE_SHINING_GAME_PROJECT_237_LOREMENU_H
