//
// Created by Kirsten on 19/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_PROJECTILE_H
#define THE_SHINING_GAME_PROJECT_237_PROJECTILE_H

<<<<<<< refs/remotes/origin/development:src/game/Objects/Items/Projectile.h
#include "../GameObject.h"
=======
#include "../Utility/Direction.h"
#include "GameObject.h"
>>>>>>> Bottles exist :^):src/game/Objects/Projectile.h

class Projectile : public GameObject
{
 public:
  explicit Projectile(ASGE::Renderer* renderer,
                      float xPos,
                      float yPos,
                      int direction);
  ~Projectile() = default;

  void resetTimer();

  void update(float delta_time);

  void setExist(bool exi);
  bool getExist();

 private:
  int direction = 0;
  float speed = 1;
  float timer = 0;
  bool exist = false;
};

#endif // THE_SHINING_GAME_PROJECT_237_PROJECTILE_H
