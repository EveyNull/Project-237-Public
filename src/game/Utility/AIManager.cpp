//
// Created by Tau on 16/01/2020.
//

#include <Engine/DebugPrinter.h>
#include <cmath>

#include "AIManager.h"

AIManager::AIManager(std::map<std::pair<int, int>, Block>& level,
                     GameObject* n_enemy) :
  maze_map(level),
  enemy(n_enemy)
{
  final_destination_tile = current_enemy_pos;
  UpdateAIStepPos();
}

void AIManager::update(float delta_time)
{
  float move_speed = 0.f;
  if (current_state == AIState::CHASING)
  {
    move_speed = 0.25f;
  }

  Vector2 move_dir = Vector2(0, 0);
  if (current_enemy_pos != current_step_tile)
  {
    move_dir = Vector2(current_step_tile.first - current_enemy_pos.first,
                       current_step_tile.second - current_enemy_pos.second);
    move_dir.normalise();

    enemy->setPos(enemy->getPos() + (move_dir * delta_time * move_speed));
  }
}

void AIManager::UpdateKnownPlayerPos(const std::pair<int, int>& new_pos_coords)
{
  current_player_pos = new_pos_coords;
  switch (ai_difficulty)
  {
    default:
    {
      bool test = checkTileInSight(current_player_pos);
      if (test)
      {
        current_state = AIState::CHASING;
        UpdateAITargetPos(current_player_pos);
      }
      break;
    }
  }
  UpdateAIStepPos();
}

Tile* AIManager::getTileFromCoords(const std::pair<int, int>& target_pos)
{
  int block_size = maze_map.at(std::pair<int, int>(0, 0)).getCols();
  Block& container_block = maze_map.at(
    std::pair<int, int>(std::floor(target_pos.first / block_size),
                        std::floor(target_pos.second / block_size)));
  return &container_block.getTile(target_pos.first % block_size,
                                  target_pos.second % block_size);
}

void AIManager::UpdateAITargetPos(const std::pair<int, int>& new_pos_target)
{
  final_destination_tile = new_pos_target;
}

void AIManager::UpdateAIStepPos()
{
  if (checkTileInSight(final_destination_tile))
  {
    current_step_tile = final_destination_tile;
  }
}

bool AIManager::checkTileInSight(const std::pair<int, int>& target_pos)
{
  if (target_pos.first - current_enemy_pos.first == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      int new_y_pos =
        current_enemy_pos.second +
        (target_pos.second - current_enemy_pos.second > 0 ? i : i * -1);
      if (!getTileFromCoords(
             std::pair<int, int>(current_enemy_pos.first, new_y_pos))
             ->getIsWalkable())
      {
        return false;
      }
      if (new_y_pos == target_pos.second)
      {
        return true;
      }
    }
  }
  else if (target_pos.second - current_enemy_pos.second == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      int new_x_pos =
        current_enemy_pos.first +
        (target_pos.first - current_enemy_pos.first > 0 ? i : i * -1);
      if (!getTileFromCoords(
             std::pair<int, int>(new_x_pos, current_enemy_pos.second))
             ->getIsWalkable())
      {
        return false;
      }
      if (new_x_pos == target_pos.first)
      {
        return true;
      }
    }
  }
  else
  {
    return false;
  }
}

void AIManager::setCurrentEnemyPos(const std::pair<int, int>& new_pos)
{
  current_enemy_pos = new_pos;
}