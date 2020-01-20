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
                     int n_tile_size);

  void update(float delta_time);

  void UpdateKnownPlayerPos(const Vector2& new_pos);
  void DecideNextMove();
  bool UpdateAITargetPos(const std::pair<int, int>& new_pos_target);
  void UpdateAIStepPos();

  Tile* getTileFromCoords(const std::pair<int, int>& target_pos);
  std::pair<int, int> getCoordsFromPos(const Vector2& target_pos);
  Vector2 getPosFromCoords(const std::pair<int, int>& target_pos);

  bool checkTileInSight(const std::pair<int, int>& target_pos);
  int getDistanceToDest(const std::pair<int, int>& coords);

  Vector2 pathFindToTarget();

  void setCurrentEnemyPos(const std::pair<int, int>& new_pos);

  Vector2 moveToPos(Vector2 intended_move, Vector2 target);

  void AddAdjacentTilesToOpenList(std::vector<PathTile>& open_list,
                                  const std::vector<PathTile>& closed_list,
                                  PathTile center_tile);

 private:
  LevelDifficulty ai_difficulty = LevelDifficulty ::EASY;

  AIState current_state = AIState ::ROAMING;

  std::map<std::pair<int, int>, Block>& maze_map;

  std::pair<int, int> final_destination_tile;
  Vector2 current_step_pos = Vector2(0, 0);

  Vector2 current_player_pos = Vector2(0, 0);
  Vector2 current_enemy_pos = Vector2(0, 0);

  GameObject* enemy = nullptr;

  int tile_size;
};

#endif // PROJECT_AIMANAGER_H
