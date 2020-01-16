//
// Created by Tau on 16/01/2020.
//
#pragma once
#ifndef PROJECT_AIMANAGER_H
#define PROJECT_AIMANAGER_H

#include "AIState.h"
#include "Direction.h"
#include "LevelDifficulty.h"
#include "../Objects/GameObject.h"
#include "../Objects/Mapping/Block.h"

class AIManager
{
public:
  explicit AIManager(std::map<std::pair<int, int>, Block>& level, GameObject* n_enemy);
  void UpdateKnownPlayerPos(std::pair<int,int> new_pos_coords);
  void UpdateAITargetPos(std::pair<int,int> new_pos_target);

  Tile* getTileFromCoords(int x, int y);

  bool checkPlayerInSight();
private:
  LevelDifficulty ai_difficulty = LevelDifficulty ::EASY;

  AIState current_state = AIState ::ROAMING;

  std::map<std::pair<int, int>, Block>& maze_map;
  Tile* final_destination_tile = nullptr;
  Tile* current_step_tile = nullptr;

  std::pair<int,int> current_player_pos = std::pair<int,int>(0,0);
  std::pair<int,int> current_enemy_pos = std::pair<int,int>(0,0);
  GameObject* enemy = nullptr;
};


#endif //PROJECT_AIMANAGER_H
