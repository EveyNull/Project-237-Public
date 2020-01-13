//
// Created by e22-watson on 06/12/2019.
//

#include "Vector2.h"

Vector2::Vector2(int n_x, int n_y)
{
  x = n_x;
  y = n_y;
}

Vector2::Vector2(float n_x, float n_y)
{
  x = n_x;
  y = n_y;
}

float Vector2::getX()
{
  return x;
}

float Vector2::getY()
{
  return y;
}

void Vector2::setX(float n_x)
{
  x = n_x;
}

void Vector2::setY(float n_y)
{
  y = n_y;
}