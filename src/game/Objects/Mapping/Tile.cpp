//
// Created by e22-watson on 06/12/2019.
//

#include "Tile.h"
Tile::Tile(ASGE::Renderer* renderer, bool isWalkable, Vector2 n_position)
{
  addSpriteComponent(renderer, "/data/1px.png");
  walkable = isWalkable;
  position = n_position;
  if (!isWalkable)
  {
    spriteComponent->getSprite()->colour(ASGE::COLOURS::GREEN);
  }
}

bool Tile::getIsWalkable()
{
  return walkable;
}

void Tile::setIsWalkable(bool isWalkable)
{
  walkable = isWalkable;
}