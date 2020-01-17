//
// Created by e22-watson on 06/12/2019.
//

#include <cmath>

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

Vector2::Vector2(double n_x, double n_y)
{
  x = n_x;
  y = n_y;
}

Vector2 Vector2::operator*(const Vector2& param)
{
  return Vector2(x * param.x, y * param.y);
}

Vector2 Vector2::operator*(float scalar)
{
  return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator+(const Vector2& param)
{
  return Vector2(x + param.x, y + param.y);
}

Vector2 Vector2::operator-(const Vector2& param)
{
  return Vector2(x - param.x, y - param.y);
}

bool Vector2::operator==(const Vector2& param)
{
  return (x == param.x && y == param.y);
}

void Vector2::normalise()
{
  auto magnitude = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
  if (magnitude > 0)
  {
    x /= magnitude;
    y /= magnitude;
  }
}

float Vector2::getX() const
{
  return x;
}

float Vector2::getY() const
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