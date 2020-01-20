//
// Created by Kirsten on 16/01/2020.
//

#include "UI.h"
#include <Engine/DebugPrinter.h>

UI::UI(ASGE::Renderer* renderer)
{
  initialiseUI(renderer);
}

void UI::initialiseUI(ASGE::Renderer* renderer)
{
  selecter.addSpriteComponent(renderer, selecter_sprite, UI_size);
  selecter.getSpriteComponent()->getSprite()->yPos(20);
  selecter.getSpriteComponent()->getSprite()->xPos(600);
  selecter.getSpriteComponent()->setVisible(true);

  bear_trap.addSpriteComponent(renderer, bear_trap_sprite, UI_size);
  bear_trap.getSpriteComponent()->getSprite()->yPos(20);
  bear_trap.getSpriteComponent()->setVisible(false);

  torch.addSpriteComponent(renderer, torch_sprite, UI_size);
  torch.getSpriteComponent()->getSprite()->yPos(20);
  torch.getSpriteComponent()->setVisible(false);

  bottle.addSpriteComponent(renderer, bottle_sprite, UI_size);
  bottle.getSpriteComponent()->getSprite()->yPos(20);
  bottle.getSpriteComponent()->setVisible(false);

  fill_bar.addSpriteComponent(renderer, fill_bar_sprite, 50);
  fill_bar.getSpriteComponent()->getSprite()->height(10);
  fill_bar.getSpriteComponent()->getSprite()->width(100);

  filler.addSpriteComponent(renderer, filler_sprite, 50);

  for (int i = 0; i < total_slots; i++)
  {
    slots[i].addSpriteComponent(renderer, slot_sprite, UI_size);
    slots[i].getSpriteComponent()->getSprite()->yPos(20);
    slots[i].getSpriteComponent()->getSprite()->xPos(600 + (i * 60));
    slots[i].getSpriteComponent()->setVisible(true);
  }
}

void UI::render(ASGE::Renderer* renderer)
{
  if (bear_trap.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*bear_trap.getSpriteComponent()->getSprite());
  }

  if (torch.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*torch.getSpriteComponent()->getSprite());
  }

  for (int i = 0; i < total_slots; i++)
  {
    renderer->renderSprite(*slots[i].getSpriteComponent()->getSprite());
  }

  if (selecter.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*selecter.getSpriteComponent()->getSprite());
  }

  if (fill_bar.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*fill_bar.getSpriteComponent()->getSprite());
  }
  if (filler.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*filler.getSpriteComponent()->getSprite());
  }
}

void UI::update(const std::deque<bool>& keys_pressed)
{
  if (keys_pressed[0])
  {
    selecter.getSpriteComponent()->getSprite()->xPos(600);
  }
  if (keys_pressed[1])
  {
    selecter.getSpriteComponent()->getSprite()->xPos(660);
  }
  if (keys_pressed[6])
  {
    selecter.getSpriteComponent()->getSprite()->xPos(720);
  }
  /*
    for (int i = 0; i < 3; i++)
    {
      if (test->anythingInSlot(i))
      {
        // CHANGE TO SWITCH WHEN OTHER ITEMS ADDED
        // Needs to be changed to:
        // Change UI when item added or removed
        int itemid = test->getItemInSlot(i);
        if (itemid == 1)
        {
          bear_trap.getSpriteComponent()->getSprite()->xPos(600 + (i * 60));
          bear_trap.getSpriteComponent()->setVisible(true);
        }
        if (itemid == 2)
        {
          torch.getSpriteComponent()->getSprite()->xPos(600 + (i * 60));
          torch.getSpriteComponent()->setVisible(true);
        }
        if (itemid == 4)
        {
          bottle.getSpriteComponent()->getSprite()->xPos(600 + (i * 60));
          bottle.getSpriteComponent()->setVisible(true);
        }
      }
    } */
}

void UI::changeSlot(int new_slot)
{
  selecter.getSpriteComponent()->getSprite()->xPos(600 + (new_slot * 60));
}

void UI::fillBar(float xpos, float ypos, float timer)
{
  fill_bar.getSpriteComponent()->getSprite()->xPos(xpos);
  fill_bar.getSpriteComponent()->getSprite()->yPos(ypos);
  fill_bar.getSpriteComponent()->setVisible(true);
  filler.getSpriteComponent()->getSprite()->xPos(xpos);
  filler.getSpriteComponent()->getSprite()->yPos(ypos);
  filler.getSpriteComponent()->setVisible(true);

  filler.getSpriteComponent()->getSprite()->width((timer / 5) * 100);
  ASGE::DebugPrinter{} << "x_pos: " << timer << std::endl;
}

void UI::stopFill()
{
  fill_bar.getSpriteComponent()->setVisible(false);
  filler.getSpriteComponent()->setVisible(false);
}