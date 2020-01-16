//
// Created by Tau on 15/01/2020.
//

#include <cmath>

#include <Engine/DebugPrinter.h>
#include "Level.h"
#include <bitset>

Level::Level(ASGE::Renderer* renderer, LevelDifficulty difficulty)
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

  if (!setUpBlocks(renderer))
  {
    throw - 1;
  }

  enemy = new GameObject();
  ai_manager = new AIManager(map, enemy);

  player = new GameObject();
  player->addSpriteComponent(renderer, "/data/1px.png", 5);
  player->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::RED);
}

void Level::update(float delta_time, const std::deque<bool>& keys_pressed)
{
  player->setPos(
    Vector2(player->getXPos() +
              (keys_pressed[3] - keys_pressed[2]) * delta_time * 0.25f,
            player->getYPos() +
              (keys_pressed[1] - keys_pressed[0]) * delta_time * 0.25f));

  int x,y;
  x = std::floor((player->getXPos() + (player->getSpriteComponent()->getSprite()->width()/2))/10);
  y = std::floor((player->getYPos() + (player->getSpriteComponent()->getSprite()->height()/2))/10);

  ASGE::DebugPrinter{} << x << "," << y << std::endl;

}

void Level::render(ASGE::Renderer* renderer, Vector2 window_size)
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

bool Level::setUpBlocks(ASGE::Renderer* renderer)
{
  for (int i = 0; i < map_width; i++)
  {
    for (int j = 0; j < map_height; j++)
    {
      BlockType block_type;
      std::bitset<2> bitset = std::bitset<2>();
      bitset[0] = (i == 0 || i == map_width - 1);
      bitset[1] = (j == 0 || j == map_height - 1);

      switch (bitset.count())
      {
        case 1:
        {
          if (bitset[0])
          {
            block_type = BlockType::X_EDGE;
          }
          else
          {
            block_type = BlockType::Y_EDGE;
          }
          break;
        }
        case 2:
        {
          block_type = BlockType::CORNER;
          break;
        }
        default:
        {
          block_type = BlockType::MIDDLE;
        }
      }
      try
      {
        Block block = Block(renderer,
                            block_type,
                            std::pair<int, int>(10, 10),
                            10,
                            std::pair<int, int>(i, j),
                            i >= map_width / 2,
                            j >= map_height / 2);
        map.emplace(std::pair<int, int>(i, j), block);
      }
      catch (int e)
      {
        if (e == -1)
        {
          return false;
        }
      }
    }
  }
  return true;
}