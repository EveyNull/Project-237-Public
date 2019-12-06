//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BLOCK_H
#define THE_SHINING_GAME_PROJECT_237_BLOCK_H

#include "../Utility/Vector2.h"
#include "Tile.h"

class Block
{
 public:
  Block(int rows, int cols);
  int getNumTiles();
  Tile* getTile(int row, int col);
  Tile* getTile(Vector2 coords);
  Tile* getTile(int tileNum);

  int getRows();
  int getCols();

 private:
  int size = 0;
  int cols = 0;
  int rows = 0;
  Tile* tiles = nullptr;
};

#endif // THE_SHINING_GAME_PROJECT_237_BLOCK_H
