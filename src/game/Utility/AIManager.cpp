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
}

void AIManager::UpdateKnownPlayerPos(std::pair<int, int> new_pos_coords)
{
  current_player_pos = new_pos_coords;
  switch (ai_difficulty)
  {
    default:
    {
      Direction player_dir = checkPlayerInSight();
      if (player_dir != Direction::NONE)
      {
        if (player_dir == 1 || player_dir == -1)
        {
          enemy->setYPos(enemy->getYPos() + player_dir);
        }
        else
        {
          enemy->setXPos(enemy->getXPos() + (player_dir / 2));
        }
      }
    }
  }
  current_enemy_pos =
    std::pair<int, int>(enemy->getXPos() / 100, enemy->getYPos() / 100);
}

Tile* AIManager::getTileFromCoords(int x, int y)
{
  int block_size = maze_map.at(std::pair<int, int>(0, 0)).getCols();
  Block& container_block = maze_map.at(std::pair<int, int>(
    std::floor(x / block_size), std::floor(y / block_size)));
  return &container_block.getTile(x % block_size, y % block_size);
}

Direction AIManager::checkPlayerInSight()
{
  if (current_player_pos.first - current_enemy_pos.first == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      int new_y_pos =
        current_enemy_pos.second +
        (current_player_pos.second - current_enemy_pos.second > 0 ? i : i * -1);
      if (new_y_pos == current_player_pos.second)
      {
        Direction dir = Direction(
          1 *
          (current_player_pos.second - current_enemy_pos.second > 0 ? 1 : -1));
        return dir;
      }
      if (!getTileFromCoords(current_enemy_pos.first, new_y_pos)
             ->getIsWalkable())
      {
        return Direction::NONE;
      }
    }
  }
  else if (current_player_pos.second - current_enemy_pos.second == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      int new_x_pos =
        current_enemy_pos.first +
        (current_player_pos.first - current_enemy_pos.first > 0 ? i : i * -1);
      if (new_x_pos == current_player_pos.first)
      {
        Direction dir = Direction(
          2 *
          (current_player_pos.first - current_enemy_pos.first > 0 ? 1 : -1));
        return dir;
      }
      if (!getTileFromCoords(new_x_pos, current_enemy_pos.second)
             ->getIsWalkable())
      {
        return Direction::NONE;
      }
    }
  }
  else
  {
    return Direction::NONE;
  }
}