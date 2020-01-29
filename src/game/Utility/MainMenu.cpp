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
  // test to get to lore menu
  if (keys_released[0])
  {
    return SceneID::LORE_MENU;
  }

  if (click_event.action == ASGE::E_MOUSE_CLICK)
  {
    MenuOption option_selected =
      checkClickedMenuOption(click_event.xpos, click_event.ypos);
    if (option_selected == MenuOption::EASY)
    {
      return SceneID::LEVEL_EASY;
    }
    else if (option_selected == MenuOption::MEDIUM)
    {
      return SceneID::LEVEL_MEDIUM;
    }
    else if (option_selected == MenuOption::HARD)
    {
      return SceneID::LEVEL_HARD;
    }
    else if (option_selected == MenuOption::LORE)
    {
      return SceneID::LORE_MENU;
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
  renderer->renderText(
    "LORE", window_size.getX() / 2, top_menu_text_ypos + 25.f + 150.f);
}

MenuOption MainMenu::checkClickedMenuOption(float xPos, float yPos)
{
  if (xPos > window_size.getX() / 2 && xPos < window_size.getX() / 2 + 100.f)
  {
    if (yPos > top_menu_text_ypos && yPos < top_menu_text_ypos + 49.f)
    {
      return MenuOption ::EASY;
    }
    else if (yPos > top_menu_text_ypos + 50 &&
             yPos < top_menu_text_ypos + 50 + 49.f)
    {
      return MenuOption ::MEDIUM;
    }
    else if (yPos > top_menu_text_ypos + 100 &&
             yPos < top_menu_text_ypos + 100 + 49.f)
    {
      return MenuOption ::HARD;
    }
    else if (yPos > top_menu_text_ypos + 150 &&
             yPos < top_menu_text_ypos + 150 + 49.f)
    {
      return MenuOption ::LORE;
    }
  }
  return MenuOption ::NO_DIFFICULTY;
}