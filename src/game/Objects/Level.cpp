//
// Created by Tau on 15/01/2020.
//

#include <cmath>

#include "Level.h"
#include <Engine/DebugPrinter.h>
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
  enemy->addSpriteComponent(renderer, "/data/1px.png", 60);
  enemy->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::RED);
  enemy->setPos(Vector2(130.f, 130.f));
  ai_manager = new AIManager(map, enemy);

  player = new GameObject();
  player->addSpriteComponent(renderer, "/data/1px.png", 60);
  player->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::BLUE);
}

void Level::update(float delta_time, const std::deque<bool>& keys_pressed)
{
  player->setPos(Vector2(
    player->getXPos() + (keys_pressed[3] - keys_pressed[2]) * delta_time * 0.5f,
    player->getYPos() +
      (keys_pressed[1] - keys_pressed[0]) * delta_time * 0.5f));

  ai_manager->UpdateKnownPlayerPos(
    std::pair<int, int>(getTileCoordsFromPos(player)));

  ai_manager->update(delta_time);
  ai_manager->setCurrentEnemyPos(getTileCoordsFromPos(enemy));
}

std::pair<int, int> Level::getTileCoordsFromPos(GameObject* object)
{
  return std::pair<int, int>(
    static_cast<int>(
      std::floor(object->getXPos() +
                 (object->getSpriteComponent()->getSprite()->width() / 2)) /
      tile_size),
    std::floor(object->getYPos() +
               (object->getSpriteComponent()->getSprite()->height() / 2)) /
      tile_size);
}

void Level::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
  {
    std::map<std::pair<int, int>, Tile>& map2 =
      iterator->second.get_all_tiles();
    for (auto jterator = map2.begin(); jterator != map2.end(); ++jterator)
    {
      setSpriteOffset(&jterator->second, window_size);
      renderer->renderSprite(
        *jterator->second.getSpriteComponent()->getSprite());
    }
  }

  setSpriteOffset(enemy, window_size);
  renderer->renderSprite(*enemy->getSpriteComponent()->getSprite());

  player->getSpriteComponent()->getSprite()->xPos(window_size.getX() / 2);
  player->getSpriteComponent()->getSprite()->yPos(window_size.getY() / 2);
  renderer->renderSprite(*player->getSpriteComponent()->getSprite());
}

void Level::setSpriteOffset(GameObject* gameObject, Vector2 window_size)
{
  gameObject->getSpriteComponent()->getSprite()->xPos(
    gameObject->getXPos() + (window_size.getX() / 2) - player->getXPos());
  gameObject->getSpriteComponent()->getSprite()->yPos(
    gameObject->getYPos() + (window_size.getY() / 2) - player->getYPos());
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
                            tile_size,
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