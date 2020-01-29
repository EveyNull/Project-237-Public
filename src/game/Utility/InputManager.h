//
// Created by joshua on 15/01/2020.
//

#ifndef PROJECT_INPUTMANAGER_H
#define PROJECT_INPUTMANAGER_H

#include <deque>

#include <Engine/OGLGame.h>

class InputManager
{
 public:
  InputManager() = default;
  static std::pair<bool, int> getMovement(const ASGE::KeyEvent* key);
  static std::pair<bool, int> getAction(const ASGE::KeyEvent* key);

  static bool keyHeld(const ASGE::KeyEvent* key);
  static bool keyReleased(const ASGE::KeyEvent* key);

  static int movement(const ASGE::KeyEvent* key);
  static int action(const ASGE::KeyEvent* key);

  void
  setKeyPressed(std::pair<bool, int> movement, std::pair<bool, int> action);

  std::pair<std::deque<bool>, std::deque<bool>> readBufferIntoKeys();

  void resetAll();

 private:
  std::deque<bool> buffer_input_held = std::deque<bool>(4);
  std::deque<bool> buffer_input_release = std::deque<bool>(12);
};

#endif // PROJECT_INPUTMANAGER_H
