//
// Created by Tau on 15/01/2020.
//
#pragma once
#include <deque>
#include <map>
#include <vector>

#include "../Utility/AIManager.h"
#include "../Utility/LevelDifficulty.h"
#include "../Utility/UI.h"
#include "GameObject.h"
#include "Mapping/Block.h"
#include "Player.h"

#include "Barrier.h"
#include "BearTrap.h"
#include "Bottle.h"
#include "Torch.h"

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
  bool setUpItems(int bear_num,
                  int bottle_num,
                  int barrier_num,
                  int torch_num,
                  ASGE::Renderer* renderer);

  int getItemAtCoords();

  void update(float delta_time, const std::deque<bool>& keys_pressed);
  void updateItems(float delta_time);
  std::pair<int, int> getTileCoordsFromPos(GameObject* object);

  void render(ASGE::Renderer* renderer, Vector2 window_size);
  void renderItems(ASGE::Renderer* renderer, Vector2 window_size);
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

  int distance_in_array = 0;

  std::vector<BearTrap> beartraps;
  std::vector<Torch> torches;
  std::vector<Barrier> barriers;
  std::vector<Bottle> bottles;
  // BearTrap* beartraps[20];
  // Torch* torches[20];
  // Barrier* barriers[20];
  // Bottle* bottles[20];
};

#endif // PROJECT_LEVEL_H
