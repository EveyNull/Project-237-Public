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

void Player::pressUse()
{
  timer = 0;
  // check on item
  float tile_check_x =
    round(((currentX + (getSpriteComponent()->getSprite()->width() / 2)) +
           (tile_size / 2)) /
          tile_size) *
      tile_size -
    (tile_size / 2) - (tile_size / 2);
  float tile_check_y =
    round(((currentY + (getSpriteComponent()->getSprite()->height() / 2)) +
           (tile_size / 2)) /
          tile_size) *
      tile_size -
    (tile_size / 2) - (tile_size / 2);

  int asdg = inventory->getItemInSlot(inv_slot);

  useItem();

  // ASGE::DebugPrinter{} << "x_pos: " << asdg << std::endl;
  // if on item, get
  // if not, use
}

void Player::pickUpItem()
{
  // pick up item on tile if inventory space
}

void Player::useItem()
{
  delaying = true;
  if (inventory->getItemInSlot(inv_slot) == BOTTLE)
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

  if (keys_pressed[6])
  {
    pressUse();
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
}

void Player::renderUI(ASGE::Renderer* renderer)
{
  ui->render(renderer);
}
