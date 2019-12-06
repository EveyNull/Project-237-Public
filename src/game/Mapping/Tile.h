//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_TILE_H
#define THE_SHINING_GAME_PROJECT_237_TILE_H

#include <engine/Sprite.h>

class Tile
{
 public:
  Tile();
  bool getIsWalkable();
  void setIsWalkable(bool isWalkable);
  void setSprite(ASGE::Sprite* n_sprite);
  ASGE::Sprite* getSprite();

 private:
  bool walkable = false;
  ASGE::Sprite* sprite;
};

#endif // THE_SHINING_GAME_PROJECT_237_TILE_H
