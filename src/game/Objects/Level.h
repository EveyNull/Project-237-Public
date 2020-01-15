//
// Created by Tau on 15/01/2020.
//

#include <deque>
#include <map>

#include "../Utility/LevelDifficulty.h"
#include "GameObject.h"
#include "Mapping/Block.h"

#ifndef PROJECT_LEVEL_H
#  define PROJECT_LEVEL_H

class Level
{
 public:
  ~Level() = default;
  Level(const Level&) = default;
  Level& operator=(const Level&) = default;
  Level(ASGE::Renderer* renderer, LevelDifficulty difficulty);
  void setUpBlocks(ASGE::Renderer* renderer);

  void update(float delta_time, const std::deque<bool>& keys_pressed);
  void render(ASGE::Renderer* renderer, Vector2 window_size);

 private:
  std::map<std::pair<int, int>, Block> map;
  GameObject* player = nullptr;
  int map_width = 0, map_height = 0;
};

#endif // PROJECT_LEVEL_H
