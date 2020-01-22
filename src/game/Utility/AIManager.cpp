//
// Created by Tau on 16/01/2020.
//

#include <Engine/DebugPrinter.h>
#include <algorithm>
#include <cmath>

#include "AIManager.h"

AIManager::AIManager(std::map<std::pair<int, int>, Block>& level,
                     GameObject* n_enemy,
                     int n_tile_size) :
  maze_map(level),
  enemy(n_enemy), tile_size(n_tile_size)
{
  current_enemy_pos = enemy->getPos();
  final_destination_tile = getCoordsFromPos(current_enemy_pos);

  UpdateAIStepPos();
}

void AIManager::update(float delta_time)
{
  float move_speed = 0.1f;
  if (current_state == AIState::CHASING)
  {
    move_speed = 0.25f;
  }

  Vector2 move_dir = Vector2(0, 0);
  if (!(current_enemy_pos == current_step_pos))
  {
    move_dir = Vector2(current_step_pos - current_enemy_pos);
    move_dir.normalise();

    enemy->setPos(
      moveToPos((enemy->getPos() + (move_dir * delta_time * move_speed)),
                current_step_pos));
    current_enemy_pos = enemy->getPos();
  }
}

Vector2 AIManager::moveToPos(Vector2 intended_move, Vector2 target)
{
  Vector2 a = intended_move - current_enemy_pos;
  Vector2 b = target - current_enemy_pos;
  if (a.getX() / b.getX() > 1)
  {
    intended_move.setX(target.getX());
  }
  if (a.getY() / b.getY() > 1)
  {
    intended_move.setY(target.getY());
  }
  return intended_move;
}

void AIManager::UpdateKnownPlayerPos(const Vector2& new_pos)
{
  if (getCoordsFromPos(new_pos) != getCoordsFromPos(current_player_pos))
  {
    current_player_pos = new_pos;
    final_destination_tile = getCoordsFromPos(current_player_pos);
    pathFindToTarget();
  }
}

void AIManager::DecideNextMove()
{
  bool changed_target = false;
  bool see_player = false;
  switch (ai_difficulty)
  {
    default:
    {
      if (checkTileInSight(getCoordsFromPos(current_player_pos)))
      {
        see_player = true;
        current_state = AIState::CHASING;
        changed_target =
          UpdateAITargetPos(getCoordsFromPos(current_player_pos));
      }
      break;
    }
  }

  if (!see_player && current_enemy_pos == current_step_pos)
  {
    current_state = AIState::ROAMING;
    switch (
      getTileFromCoords(getCoordsFromPos(current_enemy_pos))->getFootprints())
    {
      case Direction::DOWN:
      {
        final_destination_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first,
                              getCoordsFromPos(current_enemy_pos).second + 1);
        changed_target = true;
        break;
      }

      case Direction::UP:
      {
        final_destination_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first,
                              getCoordsFromPos(current_enemy_pos).second - 1);
        changed_target = true;
        break;
      }
      case Direction::RIGHT:
      {
        final_destination_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first + 1,
                              getCoordsFromPos(current_enemy_pos).second);
        changed_target = true;
        break;
      }

      case Direction::LEFT:
      {
        final_destination_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first - 1,
                              getCoordsFromPos(current_enemy_pos).second);
        changed_target = true;
        break;
      }

      default:
      {
        break;
      }
    }
    if (changed_target)
    {
      getTileFromCoords(getCoordsFromPos(current_enemy_pos))
        ->setFootprints(Direction::NONE);
    }
  }

  if (changed_target)
  {
    UpdateAIStepPos();
  }
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

std::pair<int, int> AIManager::getCoordsFromPos(const Vector2& target_pos)
{
  return std::pair<int, int>(std::floor(target_pos.getX() / tile_size),
                             std::floor(target_pos.getY() / tile_size));
}

Vector2 AIManager::getPosFromCoords(const std::pair<int, int>& target_pos)
{
  return Vector2((target_pos.first * tile_size) + (tile_size / 2),
                 target_pos.second * tile_size + (tile_size / 2));
}

bool AIManager::UpdateAITargetPos(const std::pair<int, int>& new_pos_target)
{
  if (final_destination_tile != new_pos_target)
  {
    final_destination_tile = new_pos_target;
    return true;
  }
  return false;
}

int AIManager::getDistanceToDest(const std::pair<int, int>& coords)
{
  return std::abs(final_destination_tile.first - coords.first) +
         std::abs(final_destination_tile.second - coords.second);
}

Vector2 AIManager::pathFindToTarget()
{
  PathTile current_tile =
    PathTile(0,
             getDistanceToDest(getCoordsFromPos(current_enemy_pos)),
             getCoordsFromPos(current_enemy_pos),
             getCoordsFromPos(current_enemy_pos));

  std::vector<PathTile> open_list;
  open_list.emplace_back(current_tile);
  std::vector<PathTile> closed_list;
  bool path_found = false;

  while (!path_found)
  {
    // Add tile we're looking at to the closed list and then generate its
    // children, adding them to the open list
    closed_list.emplace_back(current_tile);
    AddAdjacentTilesToOpenList(open_list, closed_list, current_tile);

    for (auto itr = open_list.begin(); itr != open_list.end(); ++itr)
    {
      if (itr->coordinates == current_tile.coordinates)
      {
        open_list.erase(itr);
        break;
      }
    }

    // Now we
    int best_weight = INFINITY;
    PathTile best_tile = open_list[0];

    for (PathTile tile : open_list)
    {
      if (tile.coordinates == final_destination_tile)
      {
        std::pair<int, int> next_tile = tile.previous_coordinates;
        while (std::find_if(closed_list.begin(),
                            closed_list.end(),
                            [&next_tile](PathTile pt) {
                              return pt.coordinates == next_tile;
                            })
                 ->previous_coordinates != getCoordsFromPos(current_enemy_pos))
        {
          path_found = true;
          next_tile = std::find_if(closed_list.begin(),
                                   closed_list.end(),
                                   [&next_tile](PathTile pt) {
                                     return pt.coordinates == next_tile;
                                   })
                        ->previous_coordinates;
        }
      }
      if (tile.weight < best_weight)
      {
        best_weight = tile.weight;
        best_tile = tile;
      }
    }
    current_tile = best_tile;
  }
}

void AIManager::AddAdjacentTilesToOpenList(
  std::vector<PathTile>& open_list,
  const std::vector<PathTile>& closed_list,
  PathTile center_tile)
{
  std::pair<int, int> adjacent_tiles[4]{
    std::pair<int, int>(center_tile.coordinates.first + 1,
                        center_tile.coordinates.second),
    std::pair<int, int>(center_tile.coordinates.first - 1,
                        center_tile.coordinates.second),
    std::pair<int, int>(center_tile.coordinates.first,
                        center_tile.coordinates.second + 1),
    std::pair<int, int>(center_tile.coordinates.first,
                        center_tile.coordinates.second - 1)
  };
  for (std::pair<int, int> new_coords : adjacent_tiles)
  {
    if (getTileFromCoords(new_coords)->getIsWalkable())
    {
      PathTile child_tile = PathTile(center_tile.step + 1,
                                     getDistanceToDest(new_coords),
                                     new_coords,
                                     center_tile.coordinates);
      if (std::find_if(
            open_list.begin(), open_list.end(), [&new_coords](PathTile pt) {
              return pt.coordinates == new_coords;
            }) == open_list.end())
      {
        if (std::find_if(closed_list.begin(),
                         closed_list.end(),
                         [&new_coords](PathTile pt) {
                           return pt.coordinates == new_coords;
                         }) == closed_list.end())
          open_list.emplace_back(child_tile);
      }
    }
  }
}

void AIManager::UpdateAIStepPos()
{
  current_step_pos = getPosFromCoords(final_destination_tile);
}

bool AIManager::checkTileInSight(const std::pair<int, int>& target_pos)
{
  std::pair<int, int> enemy_current_tile = getCoordsFromPos(current_enemy_pos);
  if (target_pos.first - enemy_current_tile.first == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      int new_y_pos =
        enemy_current_tile.second +
        (target_pos.second - enemy_current_tile.second > 0 ? i : i * -1);
      if (!getTileFromCoords(
             std::pair<int, int>(enemy_current_tile.first, new_y_pos))
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
  else if (target_pos.second - enemy_current_tile.second == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      int new_x_pos =
        enemy_current_tile.first +
        (target_pos.first - enemy_current_tile.first > 0 ? i : i * -1);
      if (!getTileFromCoords(
             std::pair<int, int>(new_x_pos, enemy_current_tile.second))
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
  current_enemy_pos = getPosFromCoords(new_pos);
}