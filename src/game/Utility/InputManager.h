//
// Created by joshua on 15/01/2020.
//

#ifndef PROJECT_INPUTMANAGER_H
#define PROJECT_INPUTMANAGER_H

#include <algorithm>
#include <deque>

#include <Engine/OGLGame.h>

class InputManager
{
 public:
  InputManager() = default;
  std::pair<bool, int> getMovement(const ASGE::KeyEvent* key);
  std::pair<bool, int> getAction(const ASGE::KeyEvent* key);

  bool keyHeld(const ASGE::KeyEvent* key);
  bool keyPressed(const ASGE::KeyEvent* key);

  int movement(const ASGE::KeyEvent* key);
  int action(const ASGE::KeyEvent* key);

  void
  setKeyPressed(std::pair<bool, int> movement, std::pair<bool, int> action);

  std::pair<std::deque<bool>, std::deque<bool>> readBufferIntoKeys();

  void resetAll();

 private:
  std::deque<bool> buffer_input_held = std::deque<bool>(4);
  std::deque<bool> buffer_input_pressed = std::deque<bool>(7);

  int keys[7] = { ASGE::KEYS::KEY_E,     ASGE::KEYS::KEY_1, ASGE::KEYS::KEY_2,
                  ASGE::KEYS::KEY_3,     ASGE::KEYS::KEY_4, ASGE::KEYS::KEY_P,
                  ASGE::KEYS::KEY_ESCAPE };
};

#endif // PROJECT_INPUTMANAGER_H
