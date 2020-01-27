//
// Created by joshua on 15/01/2020.
//

#ifndef PROJECT_INPUTMANAGER_H
#define PROJECT_INPUTMANAGER_H

#include <Engine/OGLGame.h>

class InputManager
{
 public:
  std::pair<bool, bool> getKeyAction(const ASGE::KeyEvent* key);
  std::pair<int, int> getInput(const ASGE::KeyEvent* key);

  bool getKeyDown(const ASGE::KeyEvent* key);
  bool getKeyReleased(const ASGE::KeyEvent* key);

  int getMovement(const ASGE::KeyEvent* key);
  int getPressed(const ASGE::KeyEvent* key);
};

#endif // PROJECT_INPUTMANAGER_H
