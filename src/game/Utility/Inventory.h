//
// Created by k2-wotherspoon on 17/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_INVENTORY_H
#define THE_SHINING_GAME_PROJECT_237_INVENTORY_H

#include "../Objects/BearTrap.h"
#include "../Objects/Bottle.h"
#include "../Objects/Torch.h"
#include "ItemIDs.h"

class Inventory
{
 public:
  ~Inventory() = default;
  Inventory(const Inventory&) = default;

  Inventory();

  void emptyInventory();

  // debug function
  void setInventory();

  void setSlot1(ItemIDs id, int number_change);
  void setSlot2(ItemIDs id, int number_change);
  void setSlot3(ItemIDs id, int number_change);

  void changeNumber(int Slot, int number_change);
  void setNumber(int Slot, int new_number);

  void setSlot(int Slot, int id, int number_change);
  void clearSlot(int Slot);

  int getSlotOfSameItemType(ItemIDs id);
  int getEmptySlot();

  bool anythingInSlot(int slot);
  int getItemInSlot(int slot);

  int getNumberOfSlots();

  int getAmountInSlot(int slot);

 private:
  int itemArray[9][2];

  // row is slot number
  // column: 0 = item ID, 1 = number of items

  int number_of_slots = 9;
  int number_of_columns = 2;
};

#endif // THE_SHINING_GAME_PROJECT_237_INVENTORY_H
