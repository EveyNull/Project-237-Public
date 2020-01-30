//
// Created by Joshua on 19/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_ENEMY_H
#define THE_SHINING_GAME_PROJECT_237_ENEMY_H

#include "../GameObject.h"

class Enemy : public GameObject
{
 public:
  int getHealth();
  void removeHealth();

  float getSpeed();
  void setDefaultSpeed(int AI_state);

 private:
  int health = 3;
  float speed = 0.1f;
};

#endif // THE_SHINING_GAME_PROJECT_237_ENEMY_H
