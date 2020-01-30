//
// Created by Kirsten on 19/01/2020.
//

#include "Projectile.h"
#include <Engine/DebugPrinter.h>

Projectile::Projectile(ASGE::Renderer* renderer, float xPos, float yPos, int dir)
{
  addSpriteComponent(renderer, "/data/item_images/thrownbottle.png", 50);
  spriteComponent->getSprite()->width(20);
  setExist(true);
  setXPos(xPos);
  setYPos(yPos);
  direction = dir;
  spriteComponent->setVisible(true);
  timer = 0;
}

void Projectile::update(float delta_time)
{
  if (direction == RIGHT)
  {
    setXPos(getXPos() + 1 * delta_time * speed);
  }
  else if (direction == LEFT)
  {
    setXPos(getXPos() - 1 * delta_time * speed);
  }
  else if (direction == UP)
  {
    setYPos(getYPos() - 1 * delta_time * speed);
  }
  else if (direction == DOWN)
  {
    setYPos(getYPos() + 1 * delta_time * speed);
  }

  getSpriteComponent()->getSprite()->xPos(getXPos());
  getSpriteComponent()->getSprite()->yPos(getYPos());
  timer += 5 * (delta_time / 1000);
  // ASGE::DebugPrinter{} << "x_pos: " << timer << std::endl;

  if (timer > 5)
  {
    getSpriteComponent()->setVisible(false);
  }
}

void Projectile::resetTimer()
{
  timer = 0;
}

void Projectile::setExist(bool exi)
{
  exist = exi;
}

bool Projectile::getExist()
{
  return exist;
}