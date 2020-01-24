//
// Created by Kirsten on 19/01/2020.
//

#include "Player.h"
#include <Engine/DebugPrinter.h>
#include <cmath>

Player::Player(ASGE::Renderer* renderer, float new_tile_size)
{
  addSpriteComponent(renderer, "/data/1px.png", 60);
  getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::BLUE);
  inventory = new Inventory;
  thrown_bottle = new Projectile(renderer);
  ui = new UI(renderer);
  tile_size = new_tile_size;

  inventory->setInventory();
}

int Player::pressUse(int itemID)
{
  timer = 0;

  if (itemID == EMPTY)
  {
    // check if current slot empty, if yes do nothing, if no go to use
    if (inventory->getItemInSlot(inv_slot) != 0)
    {
      useItem();
      ASGE::DebugPrinter{} << "used item" << std::endl;
      ui->update(inv_slot, itemID, inventory->getAmountInSlot(inv_slot));
      return -1;
    }
  }
  else
  {
    // check if any in inventory. if yes try to put in same slot. if cant put in
    // slot, check if any other stacks. if cant in any, check current slot.
    int asdf = getSlotToAddTo(itemID); // gets item stack slot number
    if (asdf == -1)                    // change to 0 when putting items exists
    {
      int zoop = inventory->getEmptySlot();
      if (zoop != -1)
      {
        inventory->setSlot(zoop, itemID, 1);
        // ASGE::DebugPrinter{} << "put in empty slot" << std::endl;
        ui->update(zoop, itemID, inventory->getAmountInSlot(zoop));
        return 1;
      }
    }
    else
    {
      inventory->changeNumber(asdf, 1);
      ASGE::DebugPrinter{} << asdf << std::endl;
      ui->update(asdf, itemID, inventory->getAmountInSlot(asdf));
      return 1;
    }
  }
  // ASGE::DebugPrinter{} << "nothing to use or get" << std::endl;
  return -1;
}

void Player::pickUpItem()
{
  // pick up item on tile if inventory space
}

void Player::useItem()
{
  delaying = true;
  if (inventory->getItemInSlot(inv_slot) == BOTTLE &&
      inventory->getAmountInSlot(inv_slot) > 0)
  {
    thrown_bottle->setXPos(currentX);
    thrown_bottle->setYPos(currentY);
    thrown_bottle->getSpriteComponent()->getSprite()->xPos(currentX);
    thrown_bottle->getSpriteComponent()->getSprite()->yPos(currentY);
    thrown_bottle->getSpriteComponent()->setVisible(true);
    thrown_bottle->resetTimer();
    // inventory amount -1
    inventory->changeNumber(inv_slot, -1);
  }

  if (inventory->getItemInSlot(inv_slot) == BEARTRAP)
  {
    putting = true;
    inventory->changeNumber(inv_slot, -1);
  }
}

void Player::setInvSlot(int slot)
{
  inv_slot = slot;
}

int Player::getInvSlot()
{
  return inv_slot;
}

void Player::update(const std::deque<bool>& keys_pressed, float delta_time)
{
  currentX = getXPos();
  currentY = getYPos();

  if (thrown_bottle != nullptr)
  {
    thrown_bottle->update(delta_time);
  }

  if (putting)
  {
    timer += 5 * (delta_time / 1000);
    if (timer < 5)
    {
      ui->fillBar(currentX, currentY, timer);
    }
    else
    {
      ui->stopFill();
      putting = false;
    }
  }

  // inventory slot keys
  if (keys_pressed[11])
  {
    setInvSlot(0);
    ui->changeSlot(0);
  }
  if (keys_pressed[12])
  {
    setInvSlot(1);
    ui->changeSlot(1);
  }
  if (keys_pressed[13])
  {
    setInvSlot(2);
    ui->changeSlot(2);
  }
  if (keys_pressed[14])
  {
    setInvSlot(3);
    ui->changeSlot(3);
  }
  if (keys_pressed[15])
  {
    setInvSlot(4);
    ui->changeSlot(4);
  }
  if (keys_pressed[16])
  {
    setInvSlot(5);
    ui->changeSlot(5);
  }
  if (keys_pressed[17])
  {
    setInvSlot(6);
    ui->changeSlot(6);
  }
  if (keys_pressed[18])
  {
    setInvSlot(7);
    ui->changeSlot(7);
  }
  if (keys_pressed[19])
  {
    setInvSlot(8);
    ui->changeSlot(8);
  }
}

void Player::renderUI(ASGE::Renderer* renderer)
{
  ui->render(renderer);
}

int Player::getSlotToAddTo(int itemID)
{
  for (int i = 0; i < inventory->getNumberOfSlots(); i++)
  {
    if (inventory->getItemInSlot(i) == itemID) //&& less than max amount
    {
      return i;
    }
  }
  return -1;
};
