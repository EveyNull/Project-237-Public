//
// Created by e22-watson on 06/12/2019.
//

#include <Engine/Sprite.h>

#include "Block.h"
#include <cmath>
#include <random>

Block::Block(int n_rows, int n_cols)
{
  size = n_rows * n_cols;
  rows = n_rows;
  cols = n_cols;
  tiles = new Tile[size];

  int i = size;
  while (i-- > 0)
  {
    tiles[i].setIsWalkable(rand() % 2 == 1);
  }
}

int Block::getNumTiles()
{
  return size;
}

Tile* Block::getTile(int row, int col)
{
  return &tiles[row * col];
}

Tile* Block::getTile(Vector2 vector2)
{
  return &tiles[(int)std::floor(vector2.getX()) *
                (int)std::floor(vector2.getY())];
}

Tile* Block::getTile(int tileNum)
{
  return &tiles[tileNum];
}

int Block::getRows()
{
  return rows;
}

int Block::getCols()
{
  return cols;
}