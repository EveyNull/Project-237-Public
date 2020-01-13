//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BLOCK_H
#define THE_SHINING_GAME_PROJECT_237_BLOCK_H

#include "../../Utility/Vector2.h"
#include "Tile.h"
#include <map>

class Block
{
 public:
  Block(int rows, int cols);
  Tile* getTile(int row, int col);
  Tile* getTile(std::pair<int, int> coords);

  int getRows();
  int getCols();
  float getXPos();
  float getYPos();
  std::pair<float, float> getPos();

  void setXPos(float new_pos);
  void setYPos(float new_pos);
  void setPos(std::pair<float, float> new_pos);

 private:
  int cols = 0;
  int rows = 0;
  std::map<std::pair<int, int>, Tile> tiles;

  float xPos = 0.f;
  float yPos = 0.f;
};

#endif // THE_SHINING_GAME_PROJECT_237_BLOCK_H
