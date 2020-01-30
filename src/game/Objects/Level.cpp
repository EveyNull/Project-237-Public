//
// Created by Tau on 15/01/2020.
//

#include <cmath>
#include <vector>

#include "Level.h"
#include <Engine/DebugPrinter.h>
#include <bitset>

Level::Level(ASGE::Renderer* renderer, MenuOption difficulty)
{
  switch (difficulty)
  {
    case MenuOption::EASY:
    {
      map_width = 10;
      map_height = 10;
      scene_id = SceneID::LEVEL_EASY;
      break;
    }

    case MenuOption ::MEDIUM:
    {
      map_width = 10;
      map_height = 10;
      scene_id = SceneID::LEVEL_MEDIUM;
      break;
    }

    case MenuOption ::HARD:
    {
      map_width = 15;
      map_height = 15;
      scene_id = SceneID::LEVEL_HARD;
      break;
    }

    default:
    {
      map_width = 15;
      map_height = 15;
      scene_id = SceneID::LEVEL_EASY;
      break;
    }
  }

  if (!setUpBlocks(renderer))
  {
    throw - 1;
  }

  enemy = new Enemy();

  enemy->addSpriteComponent(renderer, "/data/1px.png", tile_size * 0.75);
  enemy->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::RED);
  enemy->setPos(Vector2(330.f, 330.f));
  ai_manager = new AIManager(map, enemy, tile_size, difficulty);

  player = new Player(renderer, tile_size);
  player->addSpriteComponent(renderer, "/data/1px.png", tile_size * 0.75);
  player->setPos(Vector2(tile_size * 2 - 10.f, tile_size * 2 - 10.f));
  // player->getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::BLUE);

  render_center = player;

  player_last_tile = getTileCoordsFromPos(player);

  overlaymask = renderer->createRawSprite();
  overlaymask->loadTexture("/data/lineofsight.png");
  overlaymask->xPos(0);
  overlaymask->yPos(0);

  if (setUpSounds())
  {
    sound_enabled = true;
    soloud.play(ambience);
  }
}

Direction
Level::updateFootprintDirection(const std::pair<int, int>& player_coords)
{
  Tile& tile_left =
    map
      .at(
        std::pair<int, int>(player_last_tile.first / tiles_squared_per_block,
                            player_last_tile.second / tiles_squared_per_block))
      .getTile(
        player_last_tile.first % map.at(std::pair<int, int>(0, 0)).getCols(),
        player_last_tile.second % map.at(std::pair<int, int>(0, 0)).getRows());
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
}

SceneID Level::update(float delta_time,
                      const std::deque<bool>& input_held,
                      const std::deque<bool>& input_release,
                      const ASGE::ClickEvent& click_event)
{
  if (!paused)
  {
    if (!game_over)
    {
      std::pair<int, int> player_coords = getTileCoordsFromPos(player);
      int horizontal = input_held[3] - input_held[2];
      int vertical = input_held[1] - input_held[0];

      player->setPos(
        Vector2(player->getXPos() +
                  horizontalMovement(delta_time, horizontal, player_coords),
                player->getYPos() +
                  verticalMovement(delta_time, vertical, player_coords)));

      player->checkWalking(horizontal, vertical, delta_time);

      player->update(input_release, delta_time);
      if (player_coords != player_last_tile)
      {
        updateFootprintDirection(player_coords);
        player_last_tile = player_coords;
      }
    }

    if (input_release[0])
    {
      int item_id = 0;
      Tile* current_tile = getTileFromCoords(getTileCoordsFromPos(player));
      if (current_tile->getItem())
      {
        item_id = current_tile->getItem()->getItemID();
        current_tile->removeItem();
        player->pressUse(item_id);
      }
      player->pressUse(item_id);
    }
    isEnemyOnItem();
    ai_manager->UpdateKnownPlayerPos(player->getPos());
    ai_manager->DecideNextMove(game_over);

    ai_manager->update(delta_time);

    if (ai_manager->getUntargetable())
    {
      goop_timer += (delta_time / 1000);

      if (goop_timer >= 0.25)
      {
        // makeGoop(renderer);
        goop_timer = 0;
      }
    }

    if (getTileCoordsFromPos(player) == getTileCoordsFromPos(enemy))
    {
      game_over = true;
      render_center = enemy;
    }
  }

  if (input_release[10])
  {
    paused = !paused;
  }

  return scene_id;
}

float Level::horizontalMovement(float delta_time,
                                int horizontal,
                                std::pair<int, int> player_coords)
{
  std::pair<int, int> tile_horizontal =
    player->getWallHorizontal(horizontal, player_coords);
  if (!getTileFromCoords(tile_horizontal)->getIsWalkable())
  {
    if (player->getSpriteComponent()->getBoundingBox().isInside(
          getTileFromCoords(tile_horizontal)
            ->getSpriteComponent()
            ->getBoundingBox()))
    {
      horizontal += player_coords.first - tile_horizontal.first;
    }
  }
  return horizontal * delta_time * 0.5f;
}

float Level::verticalMovement(float delta_time,
                              int vertical,
                              std::pair<int, int> player_coords)
{
  std::pair<int, int> tile_vertical =
    player->getWallVertical(vertical, player_coords);
  if (!getTileFromCoords(tile_vertical)->getIsWalkable())
  {
    if (player->getSpriteComponent()->getBoundingBox().isInside(
          getTileFromCoords(tile_vertical)
            ->getSpriteComponent()
            ->getBoundingBox()))
    {
      vertical += player_coords.second - tile_vertical.second;
    }
  }
  return vertical * delta_time * 0.5f;
}

Tile* Level::getTileFromCoords(const std::pair<int, int>& target_pos)
{
  int block_size = map.at(std::pair<int, int>(0, 0)).getCols();
  Block& container_block =
    map.at(std::pair<int, int>(std::floor(target_pos.first / block_size),
                               std::floor(target_pos.second / block_size)));
  return &container_block.getTile(target_pos.first % block_size,
                                  target_pos.second % block_size);
}

std::pair<int, int> Level::getTileCoordsFromPos(GameObject* object)
{
  return std::pair<int, int>(
    static_cast<int>(std::floor(object->getXPos()) / tile_size),
    std::floor(object->getYPos()) / tile_size);
}

void Level::render(ASGE::Renderer* renderer, Vector2 window_size)
{
  GameObject* render_center;
  if (!game_over)
  {
    render_center = player;
  }
  else
  {
    render_center = enemy;
  }
  for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
  {
    std::map<std::pair<int, int>, Tile>& map2 =
      iterator->second.get_all_tiles();
    for (auto jterator = map2.begin(); jterator != map2.end(); ++jterator)
    {
      renderAtOffset(renderer, &jterator->second, false, window_size);
      if (jterator->second.getItem())
      {
        renderAtOffset(
          renderer, jterator->second.getItem(), false, window_size);
      }
    }
  }
  render_center->getSpriteComponent()->getSprite()->xPos(
    (window_size.getX() / 2) -
    render_center->getSpriteComponent()->getSprite()->width() / 2);
  render_center->getSpriteComponent()->getSprite()->yPos(
    (window_size.getY() / 2) -
    render_center->getSpriteComponent()->getSprite()->height() / 2);
  renderer->renderSprite(*render_center->getSpriteComponent()->getSprite());

  if (game_over)
  {
    renderer->renderText("GAME OVER",
                         window_size.getX() / 2,
                         window_size.getY() / 2 - 100.f,
                         ASGE::COLOURS::RED);
  }
  else
  {
    renderAtOffset(renderer, enemy, true, window_size);
    player->renderUI(renderer);
  }
  player->getSpriteComponent()->getSprite()->height() / 2;
  renderer->renderSprite(*player->getSpriteComponent()->getSprite());

  overlaymask->width(window_size.getX());
  overlaymask->height(window_size.getY());
  overlaymask->xPos(window_size.getX() / 2 - overlaymask->width() / 2);
  overlaymask->yPos(window_size.getY() / 2 - overlaymask->height() / 2);
  renderer->renderSprite(*overlaymask);

  if (paused)
  {
    renderer->renderText("PAUSED",
                         window_size.getX() / 2,
                         window_size.getY() / 2,
                         ASGE::COLOURS::RED);
  }
}

void Level::renderAtOffset(ASGE::Renderer* renderer,
                           GameObject* gameObject,
                           bool render_from_center,
                           Vector2 window_size)
{
  gameObject->getSpriteComponent()->getSprite()->xPos(gameObject->getXPos() +
                                                      (window_size.getX() / 2) -
                                                      render_center->getXPos());
  gameObject->getSpriteComponent()->getSprite()->yPos(gameObject->getYPos() +
                                                      (window_size.getY() / 2) -
                                                      render_center->getYPos());

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

BlockType getBlockType(const std::bitset<2>& bitset)
{
  switch (bitset.count())
  {
    case 1:
    {
      if (bitset[0])
      {
        return BlockType::X_EDGE;
      }
      else
      {
        return BlockType::Y_EDGE;
      }
    }
    case 2:
    {
      return BlockType::CORNER;
    }
    default:
    {
      return BlockType::MIDDLE;
    }
  }
}

std::vector<int> pickBlocksToSpawnItems(int num_blocks, int num_items)
{
  std::vector<int> block_numbers = std::vector<int>();

  while (block_numbers.size() < num_items)
  {
    int block_number = 0;
    do
    {
      block_number = rand() % num_blocks;
    } while (
      (std::find(block_numbers.begin(), block_numbers.end(), block_number) !=
       block_numbers.end()));
    block_numbers.emplace_back(block_number);
  }
  return block_numbers;
}

bool Level::setUpBlocks(ASGE::Renderer* renderer)
{
  std::vector<int> items_at = pickBlocksToSpawnItems(
    map_width * map_height,
    spawn_barriers + spawn_beartraps + spawn_bottles + spawn_torches);

  // REMOVE always places object at 0th block for debugging
  items_at.emplace_back(0);

  for (int i = 0; i < map_width; i++)
  {
    for (int j = 0; j < map_height; j++)
    {
      BlockType block_type;
      std::bitset<2> bitset = std::bitset<2>();
      bitset[0] = (i == 0 || i == map_width - 1);
      bitset[1] = (j == 0 || j == map_height - 1);

      block_type = getBlockType(bitset);

      try
      {
        Item* add_item = nullptr;
        if (std::find(items_at.begin(), items_at.end(), (j * 10) + i) !=
            items_at.end())
        {
          add_item = pickItemForPlacing(renderer);
          items.emplace_back(add_item);
        }
        Block block = Block(
          renderer,
          block_type,
          add_item,
          std::pair<int, int>(tiles_squared_per_block, tiles_squared_per_block),
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

Item* Level::pickItemForPlacing(ASGE::Renderer* renderer)
{
  Item* new_item = nullptr;
  while (!new_item)
  {
    switch (rand() % 4)
    {
      case 1:
      {
        if (spawn_barriers > 0)
        {
          new_item = new Barrier(renderer, tile_size);
          spawn_beartraps--;
        }
        break;
      }
      case 2:
      {
        if (spawn_bottles > 0)
        {
          new_item = new Bottle(renderer, tile_size);
          spawn_barriers--;
        }
        break;
      }
      case 3:
      {
        if (spawn_torches > 0)
        {
          new_item = new Torch(renderer, tile_size);
          spawn_torches--;
        }
        break;
      }
      default:
      {
        if (spawn_beartraps > 0)
        {
          new_item = new BearTrap(renderer, tile_size);
          spawn_beartraps--;
        }
        break;
      }
    }
  }
  return new_item;
}

bool Level::setUpSounds()
{
  if (soloud.init() == SoLoud::SO_NO_ERROR)
  {
    for (int i = 0; i < 4; i++)
    {
      loadWav(sounds[i], angry_noises[i]);
    }
    loadWav(ambient_track, ambience);
    ambience.setLooping(true);
    return true;
  }
  else
  {
    ASGE::DebugPrinter{} << "Failed to initialise SoLoud" << std::endl;
    return false;
  }
}

void Level::loadWav(const std::string& path, SoLoud::Wav& sound)
{
  ASGE::FILEIO::File file;
  if (file.open(path))
  {
    auto io_buffer = file.read();
    if (sound.loadMem(io_buffer.as_unsigned_char(),
                      static_cast<unsigned int>(io_buffer.length),
                      false,
                      false))
    {
      ASGE::DebugPrinter{} << "Failed to load sound" << std::endl;
    }
    file.close();
  }
  else
  {
    ASGE::DebugPrinter{} << "Failed to open file: " << path << std::endl;
  }
}

void Level::isEnemyOnItem()
{
  Tile* current_tile = getTileFromCoords(getTileCoordsFromPos(enemy));
  if (current_tile->getItem())
  {
    int item_id = current_tile->getItem()->getItemID();
    if (item_id == BEARTRAP - 1) // Why does it return the wrong ID?
    {
      Item* asdf = current_tile->getItem();
      if (current_tile->getItem()->getEnabled())
      {
        ASGE::DebugPrinter{} << item_id << std::endl;
        ai_manager->hitByBearTrap();
        asdf->setEnabled(false);
        asdf->update(tile_size, 2, 0);
      }
    }
  }
}

void Level::makeGoop(ASGE::Renderer* renderer)
{
  GameObject* gore = new GameObject;
  gore->addSpriteComponent(renderer, "data/splat.png", 50);
  gore->setXPos(enemy->getXPos());
  gore->setYPos(enemy->getYPos());
  goop.push_back(*gore);
}