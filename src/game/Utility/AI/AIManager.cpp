//
// Created by Tau on 16/01/2020.
//

#include <Engine/DebugPrinter.h>
#include <algorithm>
#include <cmath>

#include "AIManager.h"

AIManager::AIManager(std::map<std::pair<int, int>, Block>& level,
                     GameObject* n_enemy,
                     int n_tile_size,
                     LevelDifficulty n_difficulty) :
  maze_map(level),
  enemy(n_enemy), tile_size(n_tile_size), ai_difficulty(n_difficulty)
{
  current_enemy_pos = enemy->getPos();
  current_step_pos = current_enemy_pos;
}

void AIManager::update(float delta_time)
{
  float move_speed = 0.3f;
  if (current_state == AIState::CHASING)
  {
    move_speed = 0.5f;
  }

  if (!(current_enemy_pos == current_step_pos) && (current_state != PAUSED))
  {
    Vector2 move_dir = Vector2(current_step_pos - current_enemy_pos);
    move_dir.normalise();

    enemy->setPos(
      moveToPos((enemy->getPos() + (move_dir * delta_time * move_speed)),
                current_step_pos));
    current_enemy_pos = enemy->getPos();
  }

  if (current_state == PAUSED)
  {
    if (timer < 1)
    {
      timer += (delta_time / 1000);
    }
    else
    {
      current_state = SEARCHING;
    }
  }

  if (untargetable)
  {
    if (untargetable_timer < 5)
    {
      untargetable_timer += (delta_time / 1000);
    }
    else
    {
      untargetable = false;
    }
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
    if (ai_difficulty == LevelDifficulty::MEDIUM &&
        getManhattanDistance(getCoordsFromPos(new_pos),
                             getCoordsFromPos(current_enemy_pos)) > 10)
    {
      return;
    }
    current_player_pos = new_pos;
  }
}

void AIManager::DecideNextMove(bool game_over)
{
  if (checkTileInSight(getCoordsFromPos(current_player_pos)) && !game_over)
  {
    current_state = AIState::CHASING;
    current_step_pos = current_player_pos;
  }
  else if (current_enemy_pos == current_step_pos)
  {
    current_state = AIState::SEARCHING;
    if (!game_over)
    {
      if (ai_difficulty != LevelDifficulty::EASY)
      {
        if (ai_difficulty == LevelDifficulty::HARD ||
            getManhattanDistance(getCoordsFromPos(current_player_pos),
                                 getCoordsFromPos(current_enemy_pos)) < 10)
        {
          current_step_pos =
            pathFindToTarget(getCoordsFromPos(current_player_pos));
        }
      }
    }
    current_state = AIState::ROAMING;
    std::pair<int, int> target_tile;
    bool footprints_found = false;
    switch (
      getTileFromCoords(getCoordsFromPos(current_enemy_pos))->getFootprints())
    {
      case Direction::DOWN:
      {
        target_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first,
                              getCoordsFromPos(current_enemy_pos).second + 1);
        footprints_found = true;
        break;
      }

      case Direction::UP:
      {
        target_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first,
                              getCoordsFromPos(current_enemy_pos).second - 1);
        footprints_found = true;
        break;
      }
      case Direction::RIGHT:
      {
        target_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first + 1,
                              getCoordsFromPos(current_enemy_pos).second);
        footprints_found = true;
        break;
      }

      case Direction::LEFT:
      {
        target_tile =
          std::pair<int, int>(getCoordsFromPos(current_enemy_pos).first - 1,
                              getCoordsFromPos(current_enemy_pos).second);
        footprints_found = true;
        break;
      }

      default:
      {
        break;
      }
    }
    if (footprints_found)
    {
      if (getTileFromCoords(target_tile)->getIsWalkable())
      {
        current_step_pos = getPosFromCoords(target_tile);
      }
      getTileFromCoords(getCoordsFromPos(current_enemy_pos))
        ->setFootprints(Direction::NONE);
    }
    else
    {
      std::pair<int, int> current_tile = getCoordsFromPos(current_enemy_pos);
      std::pair<int, int> tile_up =
        std::pair<int, int>(current_tile.first, current_tile.second - 1);
      std::pair<int, int> tile_right =
        std::pair<int, int>(current_tile.first + 1, current_tile.second);
      std::pair<int, int> tile_left =
        std::pair<int, int>(current_tile.first - 1, current_tile.second);
      std::pair<int, int> tile_down =
        std::pair<int, int>(current_tile.first, current_tile.second + 1);
      bool upable = getTileFromCoords(tile_up)->getIsWalkable();
      bool rightable = getTileFromCoords(tile_right)->getIsWalkable();
      bool leftable = getTileFromCoords(tile_left)->getIsWalkable();
      bool downable = getTileFromCoords(tile_down)->getIsWalkable();
      int number_of_exits = 0;
      int came_from = UP;
      if (upable)
      {
        number_of_exits++;
      }
      if (rightable)
      {
        number_of_exits++;
      }
      if (leftable)
      {
        number_of_exits++;
      }
      if (downable)
      {
        number_of_exits++;
      }

      switch (current_travel_dir)
      {
        case LEFT:
        {
          came_from = RIGHT;
          break;
        }
        case UP:
        {
          came_from = DOWN;
          break;
        }
        case DOWN:
        {
          came_from = UP;
          break;
        }
        case RIGHT:
        {
          came_from = LEFT;
          break;
        }
        default:
          break;
      }

      if (getFurthestWalkableTileInDirection(current_travel_dir) ==
          getCoordsFromPos(current_enemy_pos))
      {
        // if hit end
        if (number_of_exits >= 2)
        {
          current_travel_dir = Direction(
            chooseBetween(upable, rightable, leftable, downable, came_from));
        }
        else
        {
          current_travel_dir = Direction(came_from);
        }

        // if exits > 1 don't go in same direction as just came
      }

      if (number_of_exits > 2)
      {
        // ASGE::DebugPrinter{} << number_of_exits << std::endl;

        // choose randomly from directions that are not the one we came from
        // came_from =
        // current_step_pos =
        // pathFindToTarget(getFurthestWalkableTileInDirection(current_travel_dir))
        // current_travel_dir = Direction(rand() % 4 + 1);
        current_travel_dir = Direction(
          chooseBetween(upable, rightable, leftable, downable, came_from));
      }
      if (current_travel_dir == 0)
      {
        current_travel_dir = Direction(rand() % 4 + 1);
      }

      ASGE::DebugPrinter{} << rand() % 4 + 1 << std::endl;
      current_step_pos = pathFindToTarget(
        getFurthestWalkableTileInDirection(current_travel_dir));
    }
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

int AIManager::getManhattanDistance(const std::pair<int, int>& target_coords,
                                    const std::pair<int, int>& start_coords)
{
  return std::abs(target_coords.first - start_coords.first) +
         std::abs(target_coords.second - start_coords.second);
}

std::pair<int, int> AIManager::getFurthestWalkableTileInDirection(Direction dir)
{
  current_travel_dir = dir;
  std::pair<int, int> current_tile = getCoordsFromPos(current_enemy_pos);
  switch (dir)
  {
    case Direction::UP:
    {
      while (getTileFromCoords(
               std::pair<int, int>(current_tile.first, current_tile.second - 1))
               ->getIsWalkable())
      {
        current_tile =
          std::pair<int, int>(current_tile.first, current_tile.second - 1);
      }
      return current_tile;
    }
    case Direction::DOWN:
    {
      while (getTileFromCoords(
               std::pair<int, int>(current_tile.first, current_tile.second + 1))
               ->getIsWalkable())
      {
        current_tile =
          std::pair<int, int>(current_tile.first, current_tile.second + 1);
      }
      return current_tile;
    }
    case Direction::LEFT:
    {
      while (getTileFromCoords(
               std::pair<int, int>(current_tile.first - 1, current_tile.second))
               ->getIsWalkable())
      {
        current_tile =
          std::pair<int, int>(current_tile.first - 1, current_tile.second);
      }
      return current_tile;
    }
    case Direction::RIGHT:
    {
      while (getTileFromCoords(
               std::pair<int, int>(current_tile.first + 1, current_tile.second))
               ->getIsWalkable())
      {
        current_tile =
          std::pair<int, int>(current_tile.first + 1, current_tile.second);
      }
      return current_tile;
    }
    default:
    {
      return current_tile;
    }
  }
}

Vector2 AIManager::pathFindToTarget(const std::pair<int, int>& target_tile)
{
  PathTile current_tile = PathTile(
    0,
    getManhattanDistance(target_tile, getCoordsFromPos(current_enemy_pos)),
    getCoordsFromPos(current_enemy_pos),
    getCoordsFromPos(current_enemy_pos));

  std::vector<PathTile> open_list;
  open_list.emplace_back(current_tile);
  std::vector<PathTile> closed_list;
  int tiles_tried = 0;

  while (tiles_tried < 500)
  {
    // Add tile we're looking at to the closed list and then generate its
    // children, adding them to the open list
    closed_list.emplace_back(current_tile);
    AddAdjacentTilesToOpenList(
      target_tile, open_list, closed_list, current_tile);

    for (auto itr = open_list.begin(); itr != open_list.end(); ++itr)
    {
      if (itr->coordinates == current_tile.coordinates)
      {
        open_list.erase(itr);
        break;
      }
    }

    int best_weight = INFINITY;
    PathTile best_tile = open_list[0];

    for (PathTile tile : open_list)
    {
      if (tile.coordinates == target_tile)
      {
        closed_list.emplace_back(tile);
        std::pair<int, int> next_tile = tile.coordinates;
        while (std::find_if(closed_list.begin(),
                            closed_list.end(),
                            [&next_tile](PathTile pt) {
                              return pt.coordinates == next_tile;
                            })
                 ->previous_coordinates != getCoordsFromPos(current_enemy_pos))
        {
          next_tile = std::find_if(closed_list.begin(),
                                   closed_list.end(),
                                   [&next_tile](PathTile pt) {
                                     return pt.coordinates == next_tile;
                                   })
                        ->previous_coordinates;
        }
        return getPosFromCoords(next_tile);
      }
      if (tile.weight < best_weight)
      {
        best_weight = tile.weight;
        best_tile = tile;
      }
    }
    current_tile = best_tile;
    tiles_tried++;
  }

  return current_enemy_pos;
}

void AIManager::AddAdjacentTilesToOpenList(
  const std::pair<int, int>& target_tile,
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
      PathTile child_tile =
        PathTile(center_tile.step + 1,
                 getManhattanDistance(target_tile, new_coords),
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

void AIManager::hitByBearTrap()
{
  if (!untargetable)
  {
    timer = 0;
    enemy->removeHealth();
    if (enemy->getHealth() > 0)
    {
      current_state = PAUSED;
      untargetable = true;
      untargetable_timer = 0;
    }
    else
    {
      current_state = DEAD;
    }
  }
}

int AIManager::getState()
{
  return current_state;
}

bool AIManager::getUntargetable()
{
  return untargetable;
}

int AIManager::chooseBetween(
  bool upable, bool rightable, bool leftable, bool downable, int came_from)
{
  int number_of_exits = 0;
  if (upable)
  {
    number_of_exits++;
  }
  if (rightable)
  {
    number_of_exits++;
  }
  if (leftable)
  {
    number_of_exits++;
  }
  if (downable)
  {
    number_of_exits++;
  }

  if (number_of_exits == 2)
  {
    if (upable && came_from != UP)
    {
      return UP;
    }
    else if (downable && came_from != DOWN)
    {
      return DOWN;
    }
    else if (rightable && came_from != RIGHT)
    {
      return RIGHT;
    }
    else if (leftable && came_from != LEFT)
    {
      return LEFT;
    }
  }
  else if (number_of_exits == 3)
  {
    // Need logic here, seems complicated :(
    int random = Direction(rand() % 4 + 1);
    return random;
  }

  else if (number_of_exits == 4)
  {
    int random = Direction(rand() % 3 + 1);

    switch (came_from)
    {
      case UP:
      {
        if (random == 1)
        {
          return RIGHT;
        }
        else if (random == 2)
        {
          return LEFT;
        }
        else if (random == 3)
        {
          return DOWN;
        }
        break;
      }
      case DOWN:
      {
        if (random == 1)
        {
          return RIGHT;
        }
        else if (random == 2)
        {
          return LEFT;
        }
        else if (random == 3)
        {
          return UP;
        }
        break;
      }
      case LEFT:
      {
        if (random == 1)
        {
          return RIGHT;
        }
        else if (random == 2)
        {
          return UP;
        }
        else if (random == 3)
        {
          return DOWN;
        }
        break;
      }

      case RIGHT:
      {
        if (random == 1)
        {
          return UP;
        }
        else if (random == 2)
        {
          return LEFT;
        }
        else if (random == 3)
        {
          return DOWN;
        }
        break;
      }
      default:
        break;
    }
  }
}