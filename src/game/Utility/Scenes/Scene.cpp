//
// Created by e22-watson on 24/01/2020.
//

#include "Scene.h"

void Scene::render(ASGE::Renderer* renderer, Vector2 window_size) {}

SceneID Scene::update(float delta_time,
                      const std::deque<bool>& keys_held,
                      const std::deque<bool>& keys_released,
                      const ASGE::ClickEvent& click_event)
{
  update(delta_time, keys_held, keys_released, click_event, nullptr);
}

SceneID Scene::update(float delta_time,
                      const std::deque<bool>& keys_held,
                      const std::deque<bool>& keys_released,
                      const ASGE::ClickEvent& click_event,
                      ASGE::Renderer*)
{
  return scene_id;
}

SceneID Scene::getSceneID()
{
  return scene_id;
}
