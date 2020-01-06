//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_VECTOR2_H
#define THE_SHINING_GAME_PROJECT_237_VECTOR2_H

class Vector2
{
 public:
  Vector2() = default;
  Vector2(int x, int y);
  Vector2(float x, float y);
  float getX();
  float getY();

 private:
  float x, y;
};

#endif // THE_SHINING_GAME_PROJECT_237_VECTOR2_H
