//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "item.h"

Item::Item(ASGE::Renderer* renderer, int tile_size)
{
  addSpriteComponent(renderer);
  setEnabled(true);
  getSpriteComponent()->setVisible(true);
  item_id = -1;
}

void Item::update(int tile_size, int frame, float delta_time) {}

void Item::setEnabled(bool Enabled)
{
  enabled = Enabled;
}

bool Item::getEnabled()
{
  return enabled;
}

void Item::setInInventory(bool Inv)
{
  inInventory = Inv;
}

bool Item::getInInventory()
{
  return inInventory;
}

void Item::setState(int State)
{
  state = State;
}

int Item::getState()
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

int Item::getItemID()
{
  return item_id;
}

void Item::setFrame(int frame)
{
  frameNumber = frame;
}

int Item::getFrame()
{
  return frameNumber;
}