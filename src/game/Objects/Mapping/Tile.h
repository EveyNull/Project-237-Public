//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_TILE_H
#define THE_SHINING_GAME_PROJECT_237_TILE_H

#include <Engine/Sprite.h>

#include "../../Utility/Direction.h"
#include "../GameObject.h"

class Tile : public GameObject
{
 public:
  Tile() = delete;
  Tile(ASGE::Renderer* renderer, bool isWalkable) :
    Tile(renderer, isWalkable, 10.f, Vector2(0.f, 0.f)){};
  Tile(ASGE::Renderer* renderer,
       bool isWalkable,
       float tile_size,
       const Vector2& n_position);
  bool getIsWalkable();
  Direction& getFootprints();

  void setIsWalkable(bool isWalkable);
  void setFootprints(const Direction& new_direction);

 private:
  bool walkable = false;
  Direction footprints = Direction::NONE;
};

#endif // THE_SHINING_GAME_PROJECT_237_TILE_H
