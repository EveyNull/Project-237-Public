//
// Created by Tau on 15/01/2020.
//
#pragma once
#include <deque>
#include <map>

#include "../Utility/AIManager.h"
#include "../Utility/LevelDifficulty.h"
#include "../Utility/UI.h"
#include "GameObject.h"
#include "Mapping/Block.h"
#include "Player.h"

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
  std::pair<int, int> getTileCoordsFromPos(GameObject* object);

  void render(ASGE::Renderer* renderer, Vector2 window_size);
  void renderAtOffset(ASGE::Renderer* renderer,
                      GameObject* gameObject,
                      bool render_from_center,
                      Vector2 window_size);

  void updateFootprints(std::pair<int, int> new_tile_coords);

 private:
  AIManager* ai_manager = nullptr;
  std::map<std::pair<int, int>, Block> map;
  int tile_size = 100;
  Player* player = nullptr;
  GameObject* enemy = nullptr;
  int map_width = 0, map_height = 0;

  std::pair<int, int> player_last_tile = std::pair<int, int>(0, 0);

  UI* ui = nullptr;
};

#endif // PROJECT_LEVEL_H
