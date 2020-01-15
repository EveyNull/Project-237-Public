//
// Created by joshua on 15/01/2020.
//

#ifndef PROJECT_INPUTMANAGER_H
#define PROJECT_INPUTMANAGER_H

#include <Engine/OGLGame.h>

class InputManager
{
 public:
  bool getKeyDown(const ASGE::KeyEvent* key);
  int getKey(const ASGE::KeyEvent* key);
};

#endif // PROJECT_INPUTMANAGER_H
