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
      return useItem();
    }
  }
  else if (itemID != LORE_ITEM)
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
        ui->update(zoop, itemID, inventory->getAmountInSlot(zoop));
        return 0;
      }
    }
    else
    {
      inventory->changeNumber(asdf, 1);
      ui->update(asdf, itemID, inventory->getAmountInSlot(asdf));
      return 0;
    }
  }
  else if (itemID == LORE_ITEM)
  {
    return 0;
  }
  return -1;
}

int Player::useItem()
{
  delaying = true;
  if (inventory->getAmountInSlot(inv_slot) > 0)
  {
    switch (inventory->getItemInSlot(inv_slot))
    {
      case BOTTLE:
      {
        thrown_bottle->setXPos(currentX);
        thrown_bottle->setYPos(currentY);
        thrown_bottle->getSpriteComponent()->getSprite()->xPos(currentX);
        thrown_bottle->getSpriteComponent()->getSprite()->yPos(currentY);
        thrown_bottle->getSpriteComponent()->setVisible(true);
        thrown_bottle->resetTimer();
        inventory->changeNumber(inv_slot, -1);
        ui->update(inv_slot, BOTTLE, inventory->getAmountInSlot(inv_slot));
        return BOTTLE;
      }
      case BEARTRAP:
      {
        inventory->changeNumber(inv_slot, -1);
        ui->update(inv_slot, BEARTRAP, inventory->getAmountInSlot(inv_slot));
        return BEARTRAP;
      }
      case BARRIER:
      {
        inventory->changeNumber(inv_slot, -1);
        ui->update(inv_slot, BARRIER, inventory->getAmountInSlot(inv_slot));
        return BARRIER;
      }
      case TORCH:
      {
        inventory->changeNumber(inv_slot, -1);
        ui->update(inv_slot, TORCH, inventory->getAmountInSlot(inv_slot));
        return TORCH;
      }
      default:
        break;
    }
  }

  return -1;
}

void Player::setInvSlot(int slot)
{
  inv_slot = slot;
}

int Player::getInvSlot()
{
  return inv_slot;
}

void Player::update(const std::deque<bool>& input_release, float delta_time)
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

  for (int i = 1; i < 5; i++)
  {
    if (input_release[i])
    {
      setInvSlot(i - 1);
      ui->changeSlot(i - 1);
      break;
    }
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
