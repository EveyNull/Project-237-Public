//
// Created by c2-worden on 27/01/2020.
//

#include "LoreMenu.h"

LoreMenu::LoreMenu(ASGE::Renderer* renderer, const Vector2& window_size)
{
  for (int i = 0; i < 5; i++)
  {
    lore[i] = new GameObject();
    lore[i]->addSpriteComponent(
      renderer, "/data/lore_pictures/Lore" + std::to_string(i + 1) + ".png", 1);
    lore[i]->getSpriteComponent()->setVisible(false);
    lore[i]->getSpriteComponent()->getSprite()->width(window_size.getX());
    lore[i]->getSpriteComponent()->getSprite()->height(window_size.getY());
  }
}

bool LoreMenu::getLocked()
{
  return locked;
}

void LoreMenu::setLocked()
{
  if (locked)
  {
    locked = !locked;
  }
}

void LoreMenu::renderText(ASGE::Renderer* renderer, Vector2 window_size)
{
  renderer->renderText("LORE 1",
                       window_size.getX() / 2,
                       window_size.getY() / 2 - 200.f,
                       ASGE::COLOURS::RED);
  renderer->renderText("LORE 2",
                       window_size.getX() / 2,
                       window_size.getY() / 2 - 100.f,
                       ASGE::COLOURS::RED);
  renderer->renderText("LORE 3",
                       window_size.getX() / 2,
                       window_size.getY() / 2,
                       ASGE::COLOURS::RED);
  renderer->renderText("LORE 4",
                       window_size.getX() / 2,
                       window_size.getY() / 2 + 100.f,
                       ASGE::COLOURS::RED);
  renderer->renderText("LORE 5",
                       window_size.getX() / 2,
                       window_size.getY() / 2 + 200.f,
                       ASGE::COLOURS::RED);
}

void LoreMenu::renderLore(ASGE::Renderer* renderer,
                          Vector2 window_size,
                          const std::deque<bool>& keys_pressed)
{
  if (keys_pressed[11])
  {
    lore[0]->getSpriteComponent()->setVisible(true);
  }

  if (lore[0]->getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*lore[0]->getSpriteComponent()->getSprite());
  }
}
