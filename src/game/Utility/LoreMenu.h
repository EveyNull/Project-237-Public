//
// Created by c2-worden on 27/01/2020.
//

#include "../Objects/GameObject.h"
#include "Vector2.h"
#include <Engine/OGLGame.h>
#include <deque>

#ifndef THE_SHINING_GAME_PROJECT_237_LOREMENU_H
#  define THE_SHINING_GAME_PROJECT_237_LOREMENU_H

class LoreMenu
{
 public:
  LoreMenu() = default;
  LoreMenu(ASGE::Renderer* renderer, const Vector2& window_size);
  ~LoreMenu() = default;

  bool getLocked();
  void setLocked();

  void renderText(ASGE::Renderer* renderer, Vector2 window_size);
  void renderLore(ASGE::Renderer* renderer,
                  Vector2 window_size,
                  const std::deque<bool>& keys_pressed);

 private:
  bool locked = true;

  GameObject* lore[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
};

#endif // THE_SHINING_GAME_PROJECT_237_LOREMENU_H
