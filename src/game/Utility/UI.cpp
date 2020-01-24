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
  selecter.getSpriteComponent()->getSprite()->xPos(400);
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

  barrier.addSpriteComponent(renderer, barrier_sprite, UI_size);
  barrier.getSpriteComponent()->getSprite()->yPos(20);
  barrier.getSpriteComponent()->setVisible(false);

  fill_bar.addSpriteComponent(renderer, fill_bar_sprite, 50);
  fill_bar.getSpriteComponent()->getSprite()->height(10);
  fill_bar.getSpriteComponent()->getSprite()->width(100);

  filler.addSpriteComponent(renderer, filler_sprite, 50);

  for (int i = 0; i < total_slots; i++)
  {
    slots[i].addSpriteComponent(renderer, slot_sprite, UI_size);
    slots[i].getSpriteComponent()->getSprite()->yPos(20);
    slots[i].getSpriteComponent()->getSprite()->xPos(400 + (i * 60));
    slots[i].getSpriteComponent()->setVisible(true);

    for (int j = 0; j < 2; j++)
    {
      itemArray[i][j] = 0;
    }
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

  if (barrier.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*barrier.getSpriteComponent()->getSprite());
  }

  if (bottle.getSpriteComponent()->getVisible())
  {
    renderer->renderSprite(*bottle.getSpriteComponent()->getSprite());
  }

  for (int i = 0; i < total_slots; i++)
  {
    renderer->renderSprite(*slots[i].getSpriteComponent()->getSprite());
    std::string amount = std::to_string(itemArray[i][1]);
    renderer->renderText(amount, 400 + (i * 60), 80, 1, ASGE::COLOURS::BLACK);
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

void UI::update(int slot, int itemID, int number)
{
  itemArray[slot][0] = itemID;
  itemArray[slot][1] = number;
  ASGE::DebugPrinter{} << "ye" << +number << std::endl;

  for (int i = 0; i < total_slots; i++)
  {
    if (number > 0)
    {
      switch (itemArray[i][0])
      {
        case BOTTLE:
        {
          bottle.getSpriteComponent()->getSprite()->xPos(400 + (i * 60));
          bottle.getSpriteComponent()->setVisible(true);
          break;
        }
        case BEARTRAP:
        {
          bear_trap.getSpriteComponent()->getSprite()->xPos(400 + (i * 60));
          bear_trap.getSpriteComponent()->setVisible(true);
          break;
        }
        case BARRIER:
        {
          barrier.getSpriteComponent()->getSprite()->xPos(400 + (i * 60));
          barrier.getSpriteComponent()->setVisible(true);
          break;
        }
        case TORCH:
        {
          torch.getSpriteComponent()->getSprite()->xPos(400 + (i * 60));
          torch.getSpriteComponent()->setVisible(true);
          break;
        }
        case EMPTY:
        {
          if (torch.getSpriteComponent()->getSprite()->xPos() ==
              (400 + (i * 60)))
          {
            torch.getSpriteComponent()->setVisible(false);
          }
          else if (barrier.getSpriteComponent()->getSprite()->xPos() ==
                   (400 + (i * 60)))
          {
            barrier.getSpriteComponent()->setVisible(false);
          }
          else if (bottle.getSpriteComponent()->getSprite()->xPos() ==
                   (400 + (i * 60)))
          {
            bottle.getSpriteComponent()->setVisible(false);
          }
          else if (bear_trap.getSpriteComponent()->getSprite()->xPos() ==
                   (400 + (i * 60)))
          {
            bear_trap.getSpriteComponent()->setVisible(false);
          }

          break;
        }
        default:
          break;
      }
    }
    // IF SLOT IS EMPTY MAKE ITEM IMAGE IN SLOT INVISIBLE
  }
}

void UI::changeSlot(int new_slot)
{
  selecter.getSpriteComponent()->getSprite()->xPos(400 + (new_slot * 60));
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
  // ASGE::DebugPrinter{} << "x_pos: " << timer << std::endl;
}

void UI::stopFill()
{
  fill_bar.getSpriteComponent()->setVisible(false);
  filler.getSpriteComponent()->setVisible(false);
}