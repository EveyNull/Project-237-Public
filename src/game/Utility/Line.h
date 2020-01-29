//
// Created by e22-watson on 29/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_LINE_H
#define THE_SHINING_GAME_PROJECT_237_LINE_H

#include "Vector2.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

class Line
{
 public:
  Line(ASGE::Renderer* renderer, int height, ASGE::Colour colour);
  void drawLine(ASGE::Renderer* renderer, Vector2 start_pos, Vector2 end_pos);

 private:
  ASGE::Sprite* sprite;
  std::string texture_path = "/data/1px.png";
};

#endif // THE_SHINING_GAME_PROJECT_237_LINE_H
