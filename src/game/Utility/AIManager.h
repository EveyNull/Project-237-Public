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

class AIManager
{
 public:
  explicit AIManager(std::map<std::pair<int, int>, Block>& level,
                     GameObject* n_enemy);

  void update(float delta_time);

  void UpdateKnownPlayerPos(const std::pair<int, int>& new_pos_coords);
  void UpdateAITargetPos(const std::pair<int, int>& new_pos_target);
  void UpdateAIStepPos();

  Tile* getTileFromCoords(const std::pair<int, int>& target_pos);

  bool checkTileInSight(const std::pair<int, int>& target_pos);

  void setCurrentEnemyPos(const std::pair<int, int>& new_pos);

 private:
  LevelDifficulty ai_difficulty = LevelDifficulty ::EASY;

  AIState current_state = AIState ::ROAMING;

  std::map<std::pair<int, int>, Block>& maze_map;

  std::pair<int, int> final_destination_tile;
  std::pair<int, int> current_step_tile;

  std::pair<int, int> current_player_pos = std::pair<int, int>(0, 0);
  std::pair<int, int> current_enemy_pos = std::pair<int, int>(1, 1);

  GameObject* enemy = nullptr;
};

#endif // PROJECT_AIMANAGER_H
