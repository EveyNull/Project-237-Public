//
// Created by e22-watson on 06/12/2019.
//

#include <Engine/DebugPrinter.h>
#include <Engine/FileIO.h>
#include <Engine/Sprite.h>

#include "../../Utility/StringHelper.h"
#include "Block.h"

#include <cmath>
#include <list>
#include <random>
std::string getBlockTypeDir(const BlockType& block_type)
{
  switch (block_type)
  {
    case BlockType::CORNER:
    {
      return "corner";
    }
    case BlockType::X_EDGE:
    {
      return "x_edge";
    }
    case BlockType::Y_EDGE:
    {
      return "y_edge";
    }
    default:
    {
      return "middle";
    }
  }
}

Block::Block(ASGE::Renderer* renderer,
             BlockType block_type,
             bool spawn_item,
             const std::pair<int, int>& n_size,
             float tile_size,
             const std::pair<int, int>& map_coords,
             bool flip_x,
             bool flip_y) :
  size(n_size)
{
  using File = ASGE::FILEIO::File;
  File blockTemplate = File();

  std::string block_type_dir = getBlockTypeDir(block_type);

  std::string fileName = "/data/map_blocks//";
  fileName.insert(17,
                  std::to_string(size.first) + "x" +
                    std::to_string(size.second) + "/" + block_type_dir);
  if (ASGE::FILEIO::enumerateFiles(fileName).empty())
  {
    ASGE::DebugPrinter{} << "No files found at directory: " << fileName
                         << std::endl;
    throw - 1;
  }
  fileName.insert(
    fileName.length(),
    std::to_string(rand() % ASGE::FILEIO::enumerateFiles(fileName).size() + 1));

  if (blockTemplate.open(fileName))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    Buffer buffer = blockTemplate.read();

    if (buffer.length)
    {
      std::list<std::list<int>> tile_types = std::list<std::list<int>>();
      std::string buffer_string = static_cast<std::string>(buffer.as_char());

      std::vector<std::string> lines = StringHelper::split(buffer_string, '\n');

      for (const std::string& line : lines)
      {
        std::list<int> tile_row = std::list<int>();

        std::vector<std::string> tiles = StringHelper::split(line, ',');

        for (const std::string& tile : tiles)
        {
          tile_row.emplace_back(std::stoi(tile));
        }

        tile_types.emplace_back(tile_row);
      }
      while (tile_types.size() > size.second)
      {
        tile_types.pop_back();
      }

      if (flip_y)
      {
        tile_types.reverse();
      }

      for (int i = 0; i < size.first; i++)
      {
        std::list<int> row = tile_types.front();
        if (flip_x)
        {
          row.reverse();
        }
        for (int j = 0; j < size.second; j++)
        {
          int tile_type = row.front();
          Vector2 tile_pos =
            Vector2(map_coords.first * size.first * tile_size,
                    map_coords.second * size.second * tile_size);
          tile_pos.setX(tile_pos.getX() + j * tile_size);
          tile_pos.setY(tile_pos.getY() + i * tile_size);
          tiles.emplace(std::pair<int, int>(j, i),
                        Tile(renderer, tile_type != 1, tile_size, tile_pos));
          if (tile_type == 2)
          {
            tiles.at(std::pair<int, int>(j, i))
              .addItem(new BearTrap(
                renderer, tile_size, tile_pos.getX(), tile_pos.getY()));
          }
          row.pop_front();
        }
        tile_types.pop_front();
      }
    }
    blockTemplate.close();
  }
  else
  {
    ASGE::DebugPrinter{} << "Failed to open file: " << fileName << std::endl;
    throw - 1;
  }
}

Tile& Block::getTile(int row, int col)
{
  return tiles.at(std::pair<int, int>(row, col));
}

Tile& Block::getTile(std::pair<int, int> coords)
{
  return tiles.at(coords);
}

std::map<std::pair<int, int>, Tile>& Block::get_all_tiles()
{
  return tiles;
}

int Block::getRows()
{
  return size.first;
}

int Block::getCols()
{
  return size.second;
}