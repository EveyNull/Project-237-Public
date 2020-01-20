//
// Created by Kirsten on 19/01/2020.
//

#include "Projectile.h"
#include <Engine/DebugPrinter.h>

Projectile::Projectile(ASGE::Renderer* renderer)
{
  addSpriteComponent(renderer, "/data/item_images/thrownbottle.png", 50);
  setExist(true);
  spriteComponent->setVisible(true);
  timer = 0;
}

void Projectile::update(float delta_time)
{
  if (getSpriteComponent()->getVisible())
  {
    setXPos(getXPos() + 1 * delta_time * 0.5f);
    setYPos(getYPos() + 0 * delta_time * 0.5f);
    getSpriteComponent()->getSprite()->xPos(getXPos());
    getSpriteComponent()->getSprite()->yPos(getYPos());
    timer += 5 * (delta_time / 1000);
    // ASGE::DebugPrinter{} << "x_pos: " << timer << std::endl;

    if (timer > 5)
    {
      getSpriteComponent()->setVisible(false);
    }
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