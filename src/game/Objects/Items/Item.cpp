//
// Created by k2-wotherspoon on 13/01/2020.
//

#include "Item.h"

Item::Item(ASGE::Renderer* renderer, int)
{
  addSpriteComponent(renderer);
  getSpriteComponent()->setVisible(true);
  item_id = -1;
}

void Item::update(int tile_size, int frame, float delta_time) {}
void Item::updateTimer(float delta_time, int tile_size) {}

void Item::resetTimer()
{
  timer = 0;
}

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