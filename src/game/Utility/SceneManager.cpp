//
// Created by e22-watson on 13/01/2020.
//

#include "SceneManager.h"

SceneManager::SceneManager(ASGE::Renderer* renderer, LevelDifficulty difficulty)
{
  switch (difficulty)
  {
    case LevelDifficulty::EASY:
    {
      map_width = 10;
      map_height = 10;
      break;
    }

    default:
    {
      map_width = 20;
      map_height = 20;
      break;
    }
  }

  setUpBlocks(renderer);

  player = new GameObject();
  player->addSpriteComponent(renderer, "/data/1px.png");
  player->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::RED);
}

void SceneManager::setUpBlocks(ASGE::Renderer* renderer)
{
  for (int i = 0; i < map_width; i++)
  {
    for (int j = 0; j < map_height; j++)
    {
      Block block = Block(renderer,
                          std::pair<int, int>(10, 10),
                          Vector2(i * 10 * 10, j * 10 * 10));
      map.emplace(std::pair<int, int>(i, j), block);
    }
  }
}

void SceneManager::update(float delta_time)
{
  player->setPos(
    Vector2(player->getXPos() +
              (keys_pressed[3] - keys_pressed[2]) * delta_time * 0.25f,
            player->getYPos() +
              (keys_pressed[1] - keys_pressed[0]) * delta_time * 0.25f));
}

void SceneManager::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
  {
    std::map<std::pair<int, int>, Tile>& map2 =
      iterator->second.get_all_tiles();
    for (auto jterator = map2.begin(); jterator != map2.end(); ++jterator)
    {
      Tile& tile = jterator->second;
      ASGE::Sprite* tile_sprite = tile.getSpriteComponent()->getSprite();
      tile_sprite->xPos(tile.getXPos() + (window_size.getX() / 2) -
                        player->getXPos());
      tile_sprite->yPos(tile.getYPos() + (window_size.getY() / 2) -
                        player->getYPos());
      renderer->renderSprite(*tile_sprite);
    }
  }
  player->getSpriteComponent()->getSprite()->xPos(window_size.getX() / 2);
  player->getSpriteComponent()->getSprite()->yPos(window_size.getY() / 2);
  renderer->renderSprite(*player->getSpriteComponent()->getSprite());
}

void SceneManager::setKeyPressed(int key, bool pressed)
{
  if (keys_pressed.size() > key && key >= 0)
  {
    keys_pressed[key] = pressed;
  }
}