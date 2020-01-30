//
// Created by e22-watson on 24/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_SCENE_H
#define THE_SHINING_GAME_PROJECT_237_SCENE_H

#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>
#include <deque>

#include "../Vector2.h"
#include "SceneID.h"

class Scene
{
 public:
  virtual SceneID update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event,
                         Vector2 mouse_pos,
                         ASGE::Renderer* renderer);

  virtual SceneID update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event,
                         Vector2 mouse_pos);
  ~Scene() = default;
  virtual void render(ASGE::Renderer* renderer, Vector2 window_size);

  SceneID getSceneID();

 protected:
  SceneID scene_id = SceneID::MAIN_MENU;
};

#endif // THE_SHINING_GAME_PROJECT_237_SCENE_H
