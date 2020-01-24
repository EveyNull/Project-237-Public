//
// Created by Kirsten on 15/01/2020.
//

#include "Barrier.h"

bool Barrier::initialiseBarrier(ASGE::Renderer* renderer,
                                int tileSize,
                                float xpos,
                                float ypos)
{
  addSpriteComponent(renderer, Frame1, tileSize);
  setXPos(xpos);
  setYPos(ypos + (tileSize / 4));
  getSpriteComponent()->getSprite()->height(tileSize / 2);
  getSpriteComponent()->getSprite()->xPos(xpos);
  getSpriteComponent()->getSprite()->yPos(ypos);
  setEnabled(true);
  getSpriteComponent()->setVisible(true);
  return true;
}