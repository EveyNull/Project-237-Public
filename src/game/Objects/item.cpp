//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "item.h"

item::item(ASGE::Renderer* renderer, int tile_size)
{
  addSpriteComponent(renderer);
  setEnabled(true);
  getSpriteComponent()->setVisible(true);
}

void item::setEnabled(bool Enabled)
{
  enabled = Enabled;
}

bool item::getEnabled()
{
  return enabled;
}

void item::setInInventory(bool Inv)
{
  inInventory = Inv;
}

bool item::getInInventory()
{
  return inInventory;
}

void item::setState(int State)
{
  state = State;
}

int item::getState()
{
  return state;
}

/* void item::setVisible(bool Visible)
{
  visible = Visible;
}

bool item::getVisible()
{
  return visible;
}
 */

int item::getItemID()
{
  return item_id;
}

void item::setFrame(int frame)
{
  frameNumber = frame;
}

int item::getFrame()
{
  return frameNumber;
}