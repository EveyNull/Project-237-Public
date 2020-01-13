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

void SceneManager::update() {}

void SceneManager::render(ASGE::Renderer* renderer)
{
  for (int i = 0; i < map_width; i++)
  {
    for (int j = 0; j < map_height; j++)
    {
      Block& block = map.at(std::pair<int, int>(i, j));

      for (int a = 0; a < block.getRows(); a++)
      {
        for (int b = 0; b < block.getCols(); b++)
        {
          Tile* tile = block.getTile(a, b);
          ASGE::Sprite* tile_sprite = tile->getSpriteComponent()->getSprite();
          tile_sprite->xPos(tile->getXPos());
          tile_sprite->yPos(tile->getYPos());
          renderer->renderSprite(
            *block.getTile(a, b)->getSpriteComponent()->getSprite());
        }
      }
    }
  }
}