//
// Created by Kirsten on 15/01/2020.
//

#include "Bottle.h"

bool Bottle::initialiseBottle(ASGE::Renderer* renderer,
                              int tileSize,
                              float xpos,
                              float ypos)
{
  addSpriteComponent(renderer, Frame1, tileSize);
  ogX = xpos + (tileSize / 4);
  setXPos(ogX);
  ogY = ypos + (tileSize / 4);
  setYPos(ogY);
  getSpriteComponent()->getSprite()->height(tileSize / 2);
  getSpriteComponent()->getSprite()->width(tileSize / 2);
  getSpriteComponent()->getSprite()->xPos(xpos);
  getSpriteComponent()->getSprite()->yPos(ypos);
  setEnabled(true);
  getSpriteComponent()->setVisible(true);
  return (true);
}

void Bottle::update(float delta_time)
{
  timer += (delta_time / 1000);

  if (timer <= 0.5 || ((1 < timer) && (timer <= 1.5)))
  {
    // setXPos(ogX);
    setYPos(ogY);
  }

  if ((0.5 < timer) && (timer <= 1))
  {
    // setXPos(ogX + 10);
    setYPos(ogY + 5);
  }

  if ((1.5 < timer) && (timer <= 2))
  {
    // setXPos(ogX - 10);
    setYPos(ogY - 5);
  }

  if (timer > 2)
  {
    timer = 0;
  }
}