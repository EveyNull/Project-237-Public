//
// Created by c2-worden on 27/01/2020.
//

#include "LoreMenu.h"
#include <Engine/DebugPrinter.h>

LoreMenu::LoreMenu(const Vector2& n_window_size, ASGE::Renderer* renderer) :
  window_size(n_window_size)
{
  scene_id = SceneID::LORE_MENU;
  loadLore(renderer, window_size);

  lore_buttons = std::vector<GameObject>(6);
  for (int i = 0; i < lore_buttons.size(); i++)
  {
    lore_buttons[i].addSpriteComponent(renderer);

    lore_buttons[i].getSpriteComponent()->getSprite()->xPos(window_size.getX() /
                                                            10);
    lore_buttons[i].getSpriteComponent()->getSprite()->yPos(top_text_Ypos +
                                                            50 * i);
    lore_buttons[i].getSpriteComponent()->getSprite()->width(100.f);
    lore_buttons[i].getSpriteComponent()->getSprite()->height(25.f);
  }

  unlocked_lore = DataManager::getAllUnlockedLore();
}
SceneID LoreMenu::update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event,
                         ASGE::Renderer*)
{
  update(delta_time, keys_held, keys_released, click_event);
}
SceneID LoreMenu::update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event,
                         ASGE::Renderer*)
{
  update(delta_time, keys_held, keys_released, click_event);
}

SceneID LoreMenu::update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event)
{
  if (keys_released[11] || lore_selected == EXIT_LORE)
  {
    return SceneID::MAIN_MENU;
  }

  if (click_event.action == ASGE::E_MOUSE_CLICK)
  {
    if (lore_opened)
    {
      lore_selected = NO_LORE;
      lore_opened = false;
    }
    else
    {
      lore_selected = checkClickedLore(click_event.xpos, click_event.ypos);
      renderLore();
    }
  }

  return scene_id;
}

void LoreMenu::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  for (int i = 0; i < 5; i++)
  {
    if (lore[i]->getSpriteComponent()->getVisible())
    {
      renderer->renderSprite(*lore[i]->getSpriteComponent()->getSprite());
    }

    renderer->renderText(
      "LORE " + std::to_string(i + 1),
      lore_buttons[i].getSpriteComponent()->getSprite()->xPos(),
      lore_buttons[i].getSpriteComponent()->getSprite()->yPos() + 25.f,
      unlocked_lore[i] ? ASGE::COLOURS::GREEN : ASGE::COLOURS::RED);
  }

  renderer->renderText(
    "MAIN MENU",
    lore_buttons[5].getSpriteComponent()->getSprite()->xPos(),
    lore_buttons[5].getSpriteComponent()->getSprite()->yPos() + 25.f,
    ASGE::COLOURS::RED);
}

LoreOption LoreMenu::checkClickedLore(float xPos, float yPos)
{
  for (int i = 0; i < 6; i++)
  {
    if (lore_buttons[i].getSpriteComponent()->getBoundingBox().isInside(xPos,
                                                                        yPos))
    {
      return LoreOption(i + 1);
    }
  }
  return LoreOption ::NO_LORE;
}

void LoreMenu::loadLore(ASGE::Renderer* renderer, const Vector2& window_size)
{
  for (int i = 0; i < 5; i++)
  {
    lore[i] = new GameObject();
    lore[i]->addSpriteComponent(
      renderer, "/data/lore_pictures/Lore" + std::to_string(i + 1) + ".png", 1);
    lore[i]->getSpriteComponent()->setVisible(false);
    lore[i]->getSpriteComponent()->getSprite()->width(8 * window_size.getX() /
                                                      10);
    lore[i]->getSpriteComponent()->getSprite()->height(window_size.getY());
    lore[i]->getSpriteComponent()->getSprite()->xPos(2 * window_size.getX() /
                                                     10);
  }
}

void LoreMenu::renderLore()
{
  for (int i = 0; i < 5; i++)
  {
    if (lore_selected == NO_LORE || lore_selected == EXIT_LORE)
    {
      lore_opened = false;
    }
    else
    {
      lore_opened = true;
    }
  }

  if (lore_opened && unlocked_lore[lore_selected - 1])
  {
    if (lore_selected == LORE1)
    {
      lore[0]->getSpriteComponent()->setVisible(true);
      lore[1]->getSpriteComponent()->setVisible(false);
      lore[2]->getSpriteComponent()->setVisible(false);
      lore[3]->getSpriteComponent()->setVisible(false);
      lore[4]->getSpriteComponent()->setVisible(false);
    }
    else if (lore_selected == LORE2)
    {
      lore[1]->getSpriteComponent()->setVisible(true);
      lore[0]->getSpriteComponent()->setVisible(false);
      lore[2]->getSpriteComponent()->setVisible(false);
      lore[3]->getSpriteComponent()->setVisible(false);
      lore[4]->getSpriteComponent()->setVisible(false);
    }
    else if (lore_selected == LORE3)
    {
      lore[2]->getSpriteComponent()->setVisible(true);
      lore[0]->getSpriteComponent()->setVisible(false);
      lore[1]->getSpriteComponent()->setVisible(false);
      lore[3]->getSpriteComponent()->setVisible(false);
      lore[4]->getSpriteComponent()->setVisible(false);
    }
    else if (lore_selected == LORE4)
    {
      lore[3]->getSpriteComponent()->setVisible(true);
      lore[0]->getSpriteComponent()->setVisible(false);
      lore[1]->getSpriteComponent()->setVisible(false);
      lore[2]->getSpriteComponent()->setVisible(false);
      lore[4]->getSpriteComponent()->setVisible(false);
    }
    else if (lore_selected == LORE5)
    {
      lore[4]->getSpriteComponent()->setVisible(true);
      lore[0]->getSpriteComponent()->setVisible(false);
      lore[1]->getSpriteComponent()->setVisible(false);
      lore[2]->getSpriteComponent()->setVisible(false);
      lore[3]->getSpriteComponent()->setVisible(false);
    }
  }
  else
  {
    for (int i = 0; i < 5; i++)
    {
      lore[i]->getSpriteComponent()->setVisible(false);
    }
  }
}

/*
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
*/
