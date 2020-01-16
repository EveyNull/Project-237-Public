//
// Created by Kirsten on 16/01/2020.
//

#include "UI.h"

UI::UI(ASGE::Renderer* renderer)
{
  initialiseUI(renderer);
}

void UI::initialiseUI(ASGE::Renderer* renderer)
{
  selecter.addSpriteComponent(renderer, selecter_sprite, 50);
  // selecter.getSpriteComponent()->getSprite()->height(50);
  // selecter.getSpriteComponent()->getSprite()->width(50);
  selecter.getSpriteComponent()->getSprite()->yPos(20);
  selecter.getSpriteComponent()->getSprite()->xPos(600);
  selecter.getSpriteComponent()->setVisible(true);

  bear_trap.addSpriteComponent(renderer, bear_trap_sprite, 50);
  // bear_trap.getSpriteComponent()->getSprite()->height(50);
  // bear_trap.getSpriteComponent()->getSprite()->width(50);
  bear_trap.getSpriteComponent()->setVisible(false);

  torch.addSpriteComponent(renderer, torch_sprite, 50);
  // torch.getSpriteComponent()->getSprite()->height(50);
  // torch.getSpriteComponent()->getSprite()->width(50);
  torch.getSpriteComponent()->setVisible(false);

  bottle.addSpriteComponent(renderer, bottle_sprite, 50);
  // bottle.getSpriteComponent()->getSprite()->height(50);
  // bottle.getSpriteComponent()->getSprite()->width(50);
  bottle.getSpriteComponent()->setVisible(false);

  fill_bar.addSpriteComponent(renderer, fill_bar_sprite, 50);

  filler.addSpriteComponent(renderer, filler_sprite, 50);

  for (int i = 0; i < total_slots; i++)
  {
    slots[i].addSpriteComponent(renderer, slot_sprite, 50);
    // slots[i].getSpriteComponent()->getSprite()->height(50);
    // slots[i].getSpriteComponent()->getSprite()->width(50);
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
  if (keys_pressed[2])
  {
    selecter.getSpriteComponent()->getSprite()->xPos(720);
  }
}