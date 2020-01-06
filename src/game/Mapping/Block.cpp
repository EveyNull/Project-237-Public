//
// Created by e22-watson on 06/12/2019.
//

#include <Engine/Sprite.h>

#include "Block.h"
#include <cmath>
#include <random>

Block::Block(int n_rows, int n_cols)
{
  rows = n_rows;
  cols = n_cols;
  for (int i = 0; i < n_rows; i++)
  {
    for (int j = 0; j < n_cols; j++)
    {
      tiles.emplace(std::pair<int, int>(i, j), Tile());
      tiles.at(std::pair<int, int>(i, j))
        .setIsWalkable(i == 0 || i == n_rows - 1 || j == 0 || j == n_cols - 1);
    }
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