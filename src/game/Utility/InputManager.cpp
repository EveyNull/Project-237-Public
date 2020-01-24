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
    case ASGE::KEYS::KEY_4:
    {
      pressed = 14;
      break;
    }
    case ASGE::KEYS::KEY_5:
    {
      pressed = 15;
      break;
    }
    case ASGE::KEYS::KEY_6:
    {
      pressed = 16;
      break;
    }
    case ASGE::KEYS::KEY_7:
    {
      pressed = 17;
      break;
    }
    case ASGE::KEYS::KEY_8:
    {
      pressed = 18;
      break;
    }
    case ASGE::KEYS::KEY_9:
    {
      pressed = 19;
      break;
    }
    default:
      break;
  }

  return pressed;
}
