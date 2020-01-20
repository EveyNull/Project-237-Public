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
  ai_manager = new AIManager(map, enemy, tile_size);

  player = new Player(renderer, tile_size);
  // player->addSpriteComponent(renderer, "/data/1px.png", 60);
  // player->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::BLUE);
  player_last_tile = getTileCoordsFromPos(player);

  ui = new UI(renderer);
}

void Level::update(float delta_time, const std::deque<bool>& keys_pressed)
{
  player->setPos(Vector2(
    player->getXPos() + (keys_pressed[3] - keys_pressed[2]) * delta_time * 0.5f,
    player->getYPos() +
      (keys_pressed[1] - keys_pressed[0]) * delta_time * 0.5f));

  player->update(keys_pressed, delta_time);

  ai_manager->UpdateKnownPlayerPos(player->getPos());
  ai_manager->DecideNextMove();

  std::pair<int, int> player_coords = getTileCoordsFromPos(player);
  if (player_coords != player_last_tile)
  {
    Tile& tile_left =
      map
        .at(std::pair<int, int>(player_last_tile.first / map_width,
                                player_last_tile.second / map_height))
        .getTile(player_last_tile.first %
                   map.at(std::pair<int, int>(0, 0)).getCols(),
                 player_last_tile.second %
                   map.at(std::pair<int, int>(0, 0)).getRows());

    if (tile_left.getFootprints() == Direction::NONE)
    {
      if (player_coords.first - player_last_tile.first > 0)
        tile_left.setFootprints(Direction::RIGHT);
      else if (player_coords.first - player_last_tile.first < 0)
        tile_left.setFootprints(Direction::LEFT);
      else if (player_coords.second - player_last_tile.second > 0)
        tile_left.setFootprints(Direction::DOWN);
      else
        tile_left.setFootprints(Direction::UP);
    }
    player_last_tile = player_coords;
  }

  ai_manager->update(delta_time);
}

std::pair<int, int> Level::getTileCoordsFromPos(GameObject* object)
{
  return std::pair<int, int>(
    static_cast<int>(std::floor(object->getXPos()) / tile_size),
    std::floor(object->getYPos()) / tile_size);
}

void Level::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
  {
    std::map<std::pair<int, int>, Tile>& map2 =
      iterator->second.get_all_tiles();
    for (auto jterator = map2.begin(); jterator != map2.end(); ++jterator)
    {
      renderAtOffset(renderer, &jterator->second, false, window_size);
    }
  }

  renderAtOffset(renderer, enemy, true, window_size);
  if (player->thrown_bottle != nullptr)
  {
    renderAtOffset(renderer, player->thrown_bottle, true, window_size);
  }
  player->renderUI(renderer);

  player->getSpriteComponent()->getSprite()->xPos(
    (window_size.getX() / 2) -
    player->getSpriteComponent()->getSprite()->width() / 2);
  player->getSpriteComponent()->getSprite()->yPos(
    (window_size.getY() / 2) -
    player->getSpriteComponent()->getSprite()->height() / 2);
  renderer->renderSprite(*player->getSpriteComponent()->getSprite());
}

void Level::renderAtOffset(ASGE::Renderer* renderer,
                           GameObject* gameObject,
                           bool render_from_center,
                           Vector2 window_size)
{
  gameObject->getSpriteComponent()->getSprite()->xPos(
    gameObject->getXPos() + (window_size.getX() / 2) - player->getXPos());
  gameObject->getSpriteComponent()->getSprite()->yPos(
    gameObject->getYPos() + (window_size.getY() / 2) - player->getYPos());

  if (render_from_center)
  {
    gameObject->getSpriteComponent()->getSprite()->xPos(
      gameObject->getSpriteComponent()->getSprite()->xPos() -
      gameObject->getSpriteComponent()->getSprite()->width() / 2);
    gameObject->getSpriteComponent()->getSprite()->yPos(
      gameObject->getSpriteComponent()->getSprite()->yPos() -
      gameObject->getSpriteComponent()->getSprite()->height() / 2);
  }

  if (gameObject->getSpriteComponent()->getSprite()->xPos() > 0 &&
      gameObject->getSpriteComponent()->getSprite()->xPos() <
        window_size.getX() -
          gameObject->getSpriteComponent()->getSprite()->width()

      && gameObject->getSpriteComponent()->getSprite()->yPos() > 0 &&
      gameObject->getSpriteComponent()->getSprite()->yPos() <
        window_size.getY() -
          gameObject->getSpriteComponent()->getSprite()->height())
  {
    renderer->renderSprite(*gameObject->getSpriteComponent()->getSprite());
  }
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