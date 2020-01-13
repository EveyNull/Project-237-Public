//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_TILE_H
#define THE_SHINING_GAME_PROJECT_237_TILE_H

#include <Engine/Sprite.h>

#include "../GameObject.h"

class Tile : public GameObject
{
 public:
  Tile() = delete;
  Tile(ASGE::Renderer* renderer, bool isWalkable) :
    Tile(renderer, isWalkable, Vector2(0.f, 0.f)){};
  Tile(ASGE::Renderer* renderer, bool isWalkable, Vector2 n_position);
  bool getIsWalkable();
  void setIsWalkable(bool isWalkable);

 private:
  bool walkable = false;
};

#endif // THE_SHINING_GAME_PROJECT_237_TILE_H
