//
// Created by e22-watson on 06/12/2019.
//

#include <Engine/FileIO.h>
#include <Engine/Sprite.h>

#include "Block.h"
#include <cmath>
#include <random>
#include <list>
#include <Engine/DebugPrinter.h>


Block::Block(int n_rows, int n_cols)
{
  rows = n_rows;
  cols = n_cols;

  using File = ASGE::FILEIO::File;
  File blockTemplate = File();

  std::string fileName = "/data/map_blocks//";
  fileName.insert(17, std::to_string(n_rows) + "x" + std::to_string(n_cols));
  fileName.insert(fileName.length(), std::to_string(rand() % 2 + 1));

  if(blockTemplate.open(fileName))
  {
    using Buffer = ASGE::FILEIO::IOBuffer;
    Buffer buffer = blockTemplate.read();

    if(buffer.length)
    {
      std::list<std::list<int>> tile_types = std::list<std::list<int>>();
      std::string buffer_string = static_cast<std::string>(buffer.as_char());

      std::size_t current_line, previous_line = 0;
      current_line = buffer_string.find('\n');
      while(current_line != std::string::npos)
      {
        std::size_t current_char, previous_char = 0;
        std::string line = buffer_string.substr(previous_line, current_line - previous_line);
        current_char = line.find(',');

        std::list<int> line_data = std::list<int>();
        while(current_char != std::string::npos)
        {
          line_data.emplace_back(std::stoi(line.substr(previous_char, current_char - previous_char)));
          previous_char = current_char + 1;
          current_char = line.find(',', previous_char);
        }
        tile_types.emplace_back(line_data);

        previous_line = current_line + 1;
        current_line = buffer_string.find('\n', previous_line);
      }

      for (int i = 0; i < n_rows; i++)
      {
        std::list<int> row = tile_types.front();
        for (int j = 0; j < n_cols; j++)
        {
          tiles.emplace(std::pair<int, int>(j, i), Tile());
          int tile_type = row.front();
          tiles.at(std::pair<int, int>(j, i))
            .setIsWalkable(tile_type != 1);
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

Tile* Block::getTile(int row, int col)
{
  return &tiles.at(std::pair<int, int>(row, col));
}

Tile* Block::getTile(std::pair<int, int> coords)
{
  return &tiles.at(coords);
}

float Block::getXPos()
{
  return xPos;
}

float Block::getYPos()
{
  return yPos;
}

std::pair<float, float> Block::getPos()
{
  return std::pair<float, float>(xPos, yPos);
}

void Block::setXPos(float new_pos)
{
  xPos = new_pos;
}

void Block::setYPos(float new_pos)
{
  yPos = new_pos;
}

void Block::setPos(std::pair<float, float> new_pos)
{
  xPos = new_pos.first;
  yPos = new_pos.second;
}

int Block::getRows()
{
  return rows;
}

int Block::getCols()
{
  return cols;
}