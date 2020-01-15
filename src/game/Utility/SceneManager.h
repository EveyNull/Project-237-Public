//
// Created by e22-watson on 13/01/2020.
//

#include <deque>
#include <map>

#include "../Objects/GameObject.h"
#include "../Objects/Mapping/Block.h"
#include "../Objects/Level.h"
#include "LevelDifficulty.h"
#include "GameState.h"

#ifndef THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H
#  define THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H

class SceneManager
{
 public:
  ~SceneManager() = default;
  explicit SceneManager(ASGE::Renderer* n_renderer);
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;

  void update(float delta_time);
  void render(ASGE::Renderer* renderer, Vector2 window_size);

  void setKeyPressed(int key, bool pressed);

  void togglePause();

  GameState getGameState();

 private:
  GameState gameState = GameState::MAINMENU;
  bool paused = false;
  bool just_paused = false;

  Level* game_level = nullptr;

  ASGE::Renderer* renderer = nullptr;
  std::deque<bool> keys_pressed = std::deque<bool>(6);
};

#endif // THE_SHINING_GAME_PROJECT_237_SCENEMANAGER_H
