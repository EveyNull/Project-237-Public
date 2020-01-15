//
// Created by e22-watson on 13/01/2020.
//

#include <Engine/DebugPrinter.h>
#include "SceneManager.h"

SceneManager::SceneManager(ASGE::Renderer* n_renderer)
: renderer(n_renderer) {}

void SceneManager::update(float delta_time)
{
  if(gameState == GameState::MAINMENU)
  {
    if(keys_pressed[5])
    {
      gameState = GameState::EXITING;
      keys_pressed[5] = false;
      return;
    }
    if(keys_pressed[0])
    {
      game_level = new Level(renderer, LevelDifficulty::EASY);
      gameState = GameState::INGAME;
    }
  }
  else if(gameState == GameState::INGAME)
  {
    if(!paused)
    {
      game_level->update(delta_time, keys_pressed);
    }
    else
    {
      if(keys_pressed[5])
      {
        gameState = GameState::MAINMENU;
        delete game_level;
        keys_pressed[5] = false;
        return;
      }
    }
    if(keys_pressed[4])
    {
      togglePause();
      keys_pressed[4] = false;
    }
    else
    {
      just_paused = false;
    }
  }
}

void SceneManager::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  if(gameState == GameState::MAINMENU)
  {
    renderer->renderText("PRESS W TO START", window_size.getX()/2, window_size.getY()/2);
  }
  else if(gameState == GameState::INGAME)
  {
    game_level->render(renderer, window_size);
    if(paused)
    {
      renderer->renderText("PAUSED", window_size.getX()/2, window_size.getY()/2, ASGE::COLOURS::RED);
    }
  }
}

void SceneManager::setKeyPressed(int key, bool pressed)
{
  if (keys_pressed.size() > key && key >= 0)
  {
    keys_pressed[key] = pressed;
  }
}

void SceneManager::togglePause()
{
  paused = !paused;
}

GameState SceneManager::getGameState()
{
  return gameState;
}