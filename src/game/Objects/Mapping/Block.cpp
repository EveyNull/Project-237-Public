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

Block::Block(ASGE::Renderer* renderer,
             const std::pair<int, int>& n_size,
             Vector2 position) :
  size(n_size)
{
  using File = ASGE::FILEIO::File;
  File blockTemplate = File();

  std::string fileName = "/data/map_blocks//";
  fileName.insert(
    17, std::to_string(size.first) + "x" + std::to_string(size.second));
  fileName.insert(fileName.length(), std::to_string(rand() % 2 + 1));

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

      for (int i = 0; i < size.first; i++)
      {
        std::list<int> row = tile_types.front();
        for (int j = 0; j < size.second; j++)
        {
          int tile_type = row.front();
          Vector2 tile_pos = position;
          tile_pos.setX(tile_pos.getX() + j * 10);
          tile_pos.setY(tile_pos.getY() + i * 10);
          tiles.emplace(std::pair<int, int>(j, i),
                        Tile(renderer, tile_type != 1, tile_pos));
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