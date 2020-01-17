//
// Created by e22-watson on 06/12/2019.
//

#include <cmath>

#include "Tile.h"
Tile::Tile(ASGE::Renderer* renderer,
           bool isWalkable,
           float tile_size,
           const Vector2& n_position)
{
  addSpriteComponent(renderer, "/data/1px.png", tile_size);
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

Direction& Tile::getFootprints()
{
  return footprints;
}

void Tile::setIsWalkable(bool isWalkable)
{
  walkable = isWalkable;
}

void Tile::setFootprints(const Direction& new_direction)
{
  float tile_size = spriteComponent->getSprite()->width();
  footprints = new_direction;
  if (new_direction != Direction::NONE)
  {
    spriteComponent->getSprite()->loadTexture("/data/footprints/right.png");
  }
  else
  {
    spriteComponent->getSprite()->loadTexture("/data/1px.png");
  }
  spriteComponent->getSprite()->width(tile_size);
  spriteComponent->getSprite()->height(tile_size);
  switch (new_direction)
  {
    case Direction::LEFT:
    {
      spriteComponent->getSprite()->rotationInRadians(M_PI);
      break;
    }
    case Direction::DOWN:
    {
      spriteComponent->getSprite()->rotationInRadians(M_PI / 2);
      break;
    }
    case Direction::UP:
    {
      spriteComponent->getSprite()->rotationInRadians(3 * (M_PI / 2));
      break;
    }
    default:
    {
      break;
    }
  }
}