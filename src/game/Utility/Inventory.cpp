//
// Created by k2-wotherspoon on 17/01/2020.
//

#include "Inventory.h"

void Inventory::emptyInventory()
{
  for (int i = 0; i < number_of_slots; i++)
  {
    for (int j = 0; j < number_of_columns; j++)
    {
      itemArray[i][j] = 0;
    }
  }
}

void Inventory::setSlot(int Slot, ItemIDs id, int number_change)
{
  itemArray[Slot][0] = id;
  itemArray[Slot][1] += number_change;
}

void Inventory::changeNumber(int Slot, int number_change)
{
  itemArray[Slot][1] += number_change;
}

void Inventory::setNumber(int Slot, int new_number)
{
  itemArray[Slot][1] = new_number;
}

void Inventory::clearSlot(int Slot)
{
  itemArray[Slot][0] = EMPTY;
  itemArray[Slot][1] = 0;
}

bool Inventory::anythingInSlot(int slot)
{
  if (itemArray[slot][1] >= 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int Inventory::getItemInSlot(int slot)
{
  return itemArray[slot][0];
}

int Inventory::getSlotOfSameItemType(ItemIDs id)
{
  for (int i = 0; i < number_of_slots; i++)
  {
    if (itemArray[i][0] == id)
    {
      return i;
    }
  }
  return 0;
}

int Inventory::getEmptySlot()
{
  for (int i = 0; i < number_of_slots; i++)
  {
    if (itemArray[i][0] == 0)
    {
      return i;
    }
  }
  return 0;
}

void Inventory::setInventory()
{
  // debug function
  itemArray[0][0] = BEARTRAP;
  itemArray[0][1] = 3;
  itemArray[1][0] = EMPTY;
  itemArray[1][1] = 0;
  itemArray[2][0] = TORCH;
  itemArray[2][1] = 1;
}

Inventory::Inventory()
{
  emptyInventory();
}
