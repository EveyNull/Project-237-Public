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

void Enemy::setDefaultSpeed(int AI_state)
{
  if (AI_state == 0)
  {
    speed = 0.30f;
  }
  else if (AI_state == 1)
  {
    speed = 0.35f;
  }
  else if (AI_state == 2)
  {
    speed = 0.40f;
  }
  else if (AI_state == 3)
  {
    speed = 0.475f;
  }
}