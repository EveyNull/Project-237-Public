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
  if (isWalkable)
  {
    spriteComponent->getSprite()->loadTexture("/data/snow.png");
  }
  else
  {
    spriteComponent->getSprite()->loadTexture("/data/hedge.png");
  }
  spriteComponent->getSprite()->width(tile_size);
  spriteComponent->getSprite()->height(tile_size);
}

bool Tile::getIsWalkable()
{
  return walkable;
}

Direction& Tile::getFootprints()
{
  return footprints;
}

item* Tile::getItem()
{
  return present_item;
}

void Tile::addItem(item* n_item)
{
  present_item = n_item;
}

void Tile::removeItem()
{
  delete present_item;
  present_item = nullptr;
}

void Tile::setIsWalkable(bool isWalkable)
{
  walkable = isWalkable;
}

void Tile::setFootprints(const Direction& new_direction)
{
  if (!getIsWalkable())
  {
    return;
  }
  float tile_size = spriteComponent->getSprite()->width();
  footprints = new_direction;
  if (footprints == Direction::NONE)
  {
    spriteComponent->getSprite()->loadTexture("/data/snow.png");
  }
  else
  {
    spriteComponent->getSprite()->loadTexture("/data/footprints/right.png");
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