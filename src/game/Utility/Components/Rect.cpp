//
// Created by Joshua on 23/01/2020.
//

#include "Rect.h"

bool rect::isInside(float x_, float y_) const
{
  return (x_ >= this->x && x_ <= this->x + this->length) &&
         (y_ >= this->y && y_ <= this->y + this->height);
}

bool rect::isInside(const rect& rhs) const
{
  auto& lhs = *this;

  bool xOverlap = isBetween(lhs.x, rhs.x, rhs.x + rhs.length) ||
                  isBetween(rhs.x, lhs.x, lhs.x + lhs.length);

  bool yOverlap = isBetween(lhs.y, rhs.y, rhs.y + rhs.height) ||
                  isBetween(rhs.y, lhs.y, lhs.y + lhs.height);

  return xOverlap && yOverlap;
}

bool rect::isBetween(float value, float min, float max) const
{
  return (value >= min) && (value <= max);
}