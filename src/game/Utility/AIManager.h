//
// Created by Tau on 16/01/2020.
//
#pragma once
#ifndef PROJECT_AIMANAGER_H
#  define PROJECT_AIMANAGER_H

#  include "../Objects/GameObject.h"
#  include "../Objects/Mapping/Block.h"
#  include "AIState.h"
#  include "Direction.h"
#  include "LevelDifficulty.h"
#  include "PathTile.h"
#  include <vector>

class AIManager
{
 public:
  explicit AIManager(std::map<std::pair<int, int>, Block>& level,
                     GameObject* n_enemy,
                     int n_tile_size,
                     LevelDifficulty n_difficulty);

  void update(float delta_time);

  void UpdateKnownPlayerPos(const Vector2& new_pos);
  void DecideNextMove();

  Tile* getTileFromCoords(const std::pair<int, int>& target_pos);
  std::pair<int, int> getCoordsFromPos(const Vector2& target_pos);
  Vector2 getPosFromCoords(const std::pair<int, int>& target_pos);

  bool checkTileInSight(const std::pair<int, int>& target_pos);
  static int getManhattanDistance(const std::pair<int, int>& target_coords,
                                  const std::pair<int, int>& start_coords);

  std::pair<int, int> getFurthestWalkableTileInDirection(Direction dir);

  Vector2 pathFindToTarget(const std::pair<int, int>& target_tile);

  Vector2 moveToPos(Vector2 intended_move, Vector2 target);

  void AddAdjacentTilesToOpenList(const std::pair<int, int>& target_tile,
                                  std::vector<PathTile>& open_list,
                                  const std::vector<PathTile>& closed_list,
                                  PathTile center_tile);

 private:
  LevelDifficulty ai_difficulty = LevelDifficulty ::EASY;

  Direction current_travel_dir = Direction::NONE;

  AIState current_state = AIState ::ROAMING;

  std::map<std::pair<int, int>, Block>& maze_map;

  Vector2 current_step_pos = Vector2(0, 0);

  Vector2 current_player_pos = Vector2(0, 0);
  Vector2 current_enemy_pos = Vector2(0, 0);

  GameObject* enemy = nullptr;

  int tile_size;
};

#endif // PROJECT_AIMANAGER_H
