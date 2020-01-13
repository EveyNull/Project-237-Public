//
// Created by e22-watson on 06/12/2019.
//

#include "Tile.h"

Tile::Tile()
{
  sprite = nullptr;
}

bool Tile::getIsWalkable()
{
  return walkable;
}

void Tile::setIsWalkable(bool isWalkable)
{
  walkable = isWalkable;
}

void Tile::setSprite(ASGE::Sprite* n_sprite)
{
  sprite = n_sprite;
}

ASGE::Sprite* Tile::getSprite()
{
  return sprite;
}