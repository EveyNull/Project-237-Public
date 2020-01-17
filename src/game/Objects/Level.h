//
// Created by Tau on 15/01/2020.
//
#pragma once
#include <deque>
#include <map>

#include "../Utility/AIManager.h"
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
  bool setUpBlocks(ASGE::Renderer* renderer);

  void update(float delta_time, const std::deque<bool>& keys_pressed);
  void render(ASGE::Renderer* renderer, Vector2 window_size);
  void renderAtOffset(ASGE::Renderer* renderer,
                      GameObject* gameObject,
                      bool render_from_center,
                      Vector2 window_size);

 private:
  AIManager* ai_manager = nullptr;
  std::map<std::pair<int, int>, Block> map;
  int tile_size = 100;
  GameObject* player = nullptr;
  GameObject* enemy = nullptr;
  int map_width = 0, map_height = 0;
};

#endif // PROJECT_LEVEL_H
