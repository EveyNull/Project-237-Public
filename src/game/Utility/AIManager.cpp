//
// Created by Tau on 16/01/2020.
//

#include <cmath>
#include <Engine/DebugPrinter.h>

#include "AIManager.h"

AIManager::AIManager(std::map<std::pair<int, int>, Block> &level, GameObject* n_enemy)
: maze_map(level), enemy(n_enemy)
{}

void AIManager::UpdateKnownPlayerPos(std::pair<int, int> new_pos_coords)
{
  current_player_pos = new_pos_coords;
  switch(ai_difficulty)
  {
    default:
    {
      checkPlayerInSight();
    }
  }
}

Tile* AIManager::getTileFromCoords(int x, int y)
{
  int block_size = maze_map.at(std::pair<int,int>(0,0)).getCols();
  Block& container_block = maze_map.at(std::pair<int,int>(std::floor(x/block_size), std::floor(y/block_size)));
  return &container_block.getTile(x % block_size, y % block_size);
}

bool AIManager::checkPlayerInSight()
{
  if(current_player_pos.first - current_enemy_pos.first == 0)
  {
    for(int i = 0; i < 10; i += current_player_pos.second - current_enemy_pos.second > 0 ? 1 : -1)
    {
      int new_y_pos = current_enemy_pos.second + (current_player_pos.second - current_enemy_pos.second > 0 ? i*-1 : i);
      if(new_y_pos == current_player_pos.second)
      {
        return true;
      }
      if(!getTileFromCoords(current_enemy_pos.first, new_y_pos)->getIsWalkable())
      {
        return false;
      }
    }
  }
  else if(current_player_pos.second - current_enemy_pos.second == 0)
  {

    for(int i = 0; i < 10; i ++)
    {
      int new_x_pos = current_enemy_pos.first + (current_player_pos.first - current_enemy_pos.first > 0 ? i*-1 : i);
      if(new_x_pos == current_player_pos.first)
      {
        return true;
      }
      if(!getTileFromCoords(new_x_pos, current_enemy_pos.second)->getIsWalkable())
      {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
}