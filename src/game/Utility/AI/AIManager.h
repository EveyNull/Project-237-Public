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
#  include "MenuOption.h"
#  include "PathTile.h"
#  include <vector>

class AIManager
{
 public:
  explicit AIManager(std::map<std::pair<int, int>, Block>& level,
                     GameObject* n_enemy,
                     int n_tile_size,
                     MenuOption n_difficulty);

  void update(float delta_time);

  void UpdateKnownPlayerPos(const Vector2& new_pos);
  void DecideNextMove(bool game_over);

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

<<<<<<< refs/remotes/origin/development:src/game/Utility/AI/AIManager.h
<<<<<<< refs/remotes/origin/development:src/game/Utility/AI/AIManager.h
  int chooseBetween(
    bool upable, bool rightable, bool leftable, bool downable, int came_from);

=======
>>>>>>> a:src/game/Utility/AIManager.h
=======
  int chooseBetween(
    bool upable, bool rightable, bool leftable, bool downable, int came_from);

>>>>>>> AI buff!:src/game/Utility/AIManager.h
  void hitByBearTrap();
  void hitByBottle();
  int getState();

  bool getUntargetable();

 private:
  MenuOption ai_difficulty = MenuOption ::EASY;

  Direction current_travel_dir = Direction::NONE;

  AIState current_state = AIState ::ROAMING;

  std::map<std::pair<int, int>, Block>& maze_map;

  Vector2 current_step_pos = Vector2(0, 0);

  Vector2 current_player_pos = Vector2(0, 0);
  Vector2 current_enemy_pos = Vector2(0, 0);

  GameObject* enemy = nullptr;

  int tile_size;
  float timer = 0;
  bool pause = false;
  bool untargetable = false;
  float untargetable_timer = 0;
};

#endif // PROJECT_AIMANAGER_H
