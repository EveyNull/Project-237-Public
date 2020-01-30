//
// Created by e22-watson on 24/01/2020.
//

#include "MainMenu.h"
#include "../SceneID.h"
#include <Engine/DebugPrinter.h>

MainMenu::MainMenu(ASGE::Renderer* renderer, const Vector2& n_window_size) :
  window_size(n_window_size)
{
  scene_id = SceneID::MAIN_MENU;

  menu_buttons = std::vector<GameObject>(5);
  for (int i = 0; i < menu_buttons.size(); i++)
  {
    menu_buttons[i].addSpriteComponent(renderer, menu_button_textures[i]);
    menu_buttons[i].getSpriteComponent()->getSprite()->width(
      texture_sizes[i].first);
    menu_buttons[i].getSpriteComponent()->getSprite()->height(
      texture_sizes[i].second);
    menu_buttons[i].getSpriteComponent()->getSprite()->xPos(window_size.getX() /
                                                            2);
    menu_buttons[i].getSpriteComponent()->getSprite()->yPos(top_menu_text_ypos +
                                                            i * 100);
  }
}

SceneID MainMenu::update(float delta_time,
                         const std::deque<bool>& keys_held,
                         const std::deque<bool>& keys_released,
                         const ASGE::ClickEvent& click_event)
{
  // There's a VERY WEIRD BUG in ASGE that doesn't let me put this in the header
  // for some reason
  SceneID sceneIDs[5] = { SceneID::LEVEL_EASY,
                          SceneID::LEVEL_MEDIUM,
                          SceneID::LEVEL_HARD,
                          SceneID::LORE_MENU,
                          SceneID::CLOSE_GAME };

  if (click_event.action == ASGE::E_MOUSE_CLICK)
  {
    int i = 0;
    for (i; i < menu_buttons.size(); i++)
    {
      if (menu_buttons[i].getSpriteComponent()->getBoundingBox().isInside(
            click_event.xpos, click_event.ypos))
      {
        return sceneIDs[i];
      }
    }
  }
  return scene_id;
}

void MainMenu::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  for (GameObject gameObject : menu_buttons)
  {
    renderer->renderSprite(*gameObject.getSpriteComponent()->getSprite());
  }
  /*
  renderer->renderText(
    "EASY", window_size.getX() / 2, top_menu_text_ypos + 25.f);
  renderer->renderText(
    "MEDIUM", window_size.getX() / 2, top_menu_text_ypos + 25.f + 50.f);
  renderer->renderText(
    "HARD", window_size.getX() / 2, top_menu_text_ypos + 25.f + 100.f);
  renderer->renderText(
    "LORE", window_size.getX() / 2, top_menu_text_ypos + 25.f + 150.f);
    */
}