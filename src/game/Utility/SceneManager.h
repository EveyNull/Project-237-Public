//
// Created by e22-watson on 13/01/2020.
//

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
  void setUpBlocks(ASGE::Renderer* renderer);

  void update(bool D_PRESSED);
  void render(ASGE::Renderer* renderer);

 private:
  std::map<std::pair<int, int>, Block> map;
  GameObject* player = nullptr;
  int map_width = 0, map_height = 0;

  float x_offset = 0.f;
};

#endif // THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H
