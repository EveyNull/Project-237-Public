//
// Created by Joshua on 19/01/2020.
//

#include "Enemy.h"

int Enemy::getHealth()
{
  return health;
}

void Enemy::removeHealth()
{
  health--;
}

float Enemy::getSpeed()
{
  return speed;
}

void Enemy::setSpeed(int AI_state)
{
  if (AI_state == 0)
  {
    speed = 0.1f;
  }
  else if (AI_state == 1)
  {
    speed = 0.15f;
  }
  else if (AI_state == 2)
  {
    speed = 0.2f;
  }
  else if (AI_state == 3)
  {
    speed = 0.35f;
  }
}