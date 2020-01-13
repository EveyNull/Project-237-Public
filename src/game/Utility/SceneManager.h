//
// Created by e22-watson on 13/01/2020.
//

#include <bitset>
#include <map>

#include "../Objects/GameObject.h"
#include "../Objects/Mapping/Block.h"
#include "LevelDifficulty.h"

#ifndef THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H
#  define THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H

class SceneManager
{
 public:
  SceneManager(ASGE::Renderer* renderer, LevelDifficulty difficulty);
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;

  void setUpBlocks(ASGE::Renderer* renderer);

  void update(float delta_time);
  void render(ASGE::Renderer* renderer, Vector2 window_size);

  void setKeyPressed(int key, bool pressed);

 private:
  std::map<std::pair<int, int>, Block> map;
  GameObject* player = nullptr;
  int map_width = 0, map_height = 0;

  std::bitset<4> keys_pressed = std::bitset<4>(false);
};

#endif // THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H
