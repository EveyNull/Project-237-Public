//
// Created by k2-wotherspoon on 13/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_ITEM_H
#define THE_SHINING_GAME_PROJECT_237_ITEM_H

#include "GameObject.h"

class item : public GameObject
{
 public:
  void setState(int State);
  int getState();

  void setEnabled(bool Enabled);
  bool getEnabled();

  void setVisible(bool Visible);
  bool getVisible();

  void setInInventory(bool Inv);
  bool getInInventory();

  void setFrame(int frame);
  int getFrame();

  int getItemID();

 protected:
  int item_id;

  bool inInventory = false;

  bool enabled = false;

  bool visible = false;

  int state = 0;

  int frameNumber = 1;

  float xPos = 0;
  float yPos = 0;
};

#endif // THE_SHINING_GAME_PROJECT_237_ITEM_H
