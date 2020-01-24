//
// Created by e22-watson on 24/01/2020.
//

#include "MainMenu.h"
#include "SceneID.h"

MainMenu::MainMenu(const Vector2& n_window_size) : window_size(n_window_size)
{
  scene_id = SceneID::MAIN_MENU;
}

SceneID MainMenu::update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event)
{
  if (keys_released[5])
  {
    return SceneID::CLOSE_GAME;
  }
  if (click_event.action == ASGE::E_MOUSE_CLICK)
  {
    LevelDifficulty difficulty_selected =
      checkClickedDifficulty(click_event.xpos, click_event.ypos);
    if (difficulty_selected == LevelDifficulty::EASY)
    {
      return SceneID::LEVEL_EASY;
    }
    else if (difficulty_selected == LevelDifficulty::MEDIUM)
    {
      return SceneID::LEVEL_MEDIUM;
    }
    else if (difficulty_selected == LevelDifficulty::HARD)
    {
      return SceneID::LEVEL_HARD;
    }
  }
  return scene_id;
}

void MainMenu::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  renderer->renderText(
    "EASY", window_size.getX() / 2, top_menu_text_ypos + 25.f);
  renderer->renderText(
    "MEDIUM", window_size.getX() / 2, top_menu_text_ypos + 25.f + 50.f);
  renderer->renderText(
    "HARD", window_size.getX() / 2, top_menu_text_ypos + 25.f + 100.f);
}

LevelDifficulty MainMenu::checkClickedDifficulty(float xPos, float yPos)
{
  if (xPos > window_size.getX() / 2 && xPos < window_size.getX() / 2 + 100.f)
  {
    if (yPos > top_menu_text_ypos && yPos < top_menu_text_ypos + 49.f)
    {
      return LevelDifficulty ::EASY;
    }
    if (yPos > top_menu_text_ypos + 50 && yPos < top_menu_text_ypos + 50 + 49.f)
    {
      return LevelDifficulty ::MEDIUM;
    }
    if (yPos > top_menu_text_ypos + 100 &&
        yPos < top_menu_text_ypos + 100 + 49.f)
    {
      return LevelDifficulty ::HARD;
    }
  }
  return LevelDifficulty ::NO_DIFFICULTY;
}