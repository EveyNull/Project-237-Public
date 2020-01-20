//
// Created by joshua on 15/01/2020.
//

#include "InputManager.h"

bool InputManager::getKeyDown(const ASGE::KeyEvent* key)
{
  bool held = true;

  if (key->action == ASGE::KEYS::KEY_RELEASED)
  {
    held = false;
  }

  return held;
}

int InputManager::getKey(const ASGE::KeyEvent* key)
{
  int pressed = -1;

  switch (key->key)
  {
    case ASGE::KEYS::KEY_W:
    {
      pressed = 0;
      break;
    }
    case ASGE::KEYS::KEY_S:
    {
      pressed = 1;
      break;
    }
    case ASGE::KEYS::KEY_A:
    {
      pressed = 2;
      break;
    }
    case ASGE::KEYS::KEY_D:
    {
      pressed = 3;
      break;
    }
    case ASGE::KEYS::KEY_P:
    {
      pressed = 4;
      break;
    }
    case ASGE::KEYS::KEY_ESCAPE:
    {
      pressed = 5;
      break;
    }
    case ASGE::KEYS::KEY_E:
    {
      pressed = 6;
      break;
    }
    case ASGE::KEYS::KEY_1:
    {
      pressed = 11;
      break;
    }
    case ASGE::KEYS::KEY_2:
    {
      pressed = 12;
      break;
    }
    case ASGE::KEYS::KEY_3:
    {
      pressed = 13;
      break;
    }
    default:
      break;
  }

  return pressed;
}
