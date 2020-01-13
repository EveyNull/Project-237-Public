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
  Block(ASGE::Renderer* renderer,
        const std::pair<int, int>& n_size,
        Vector2 position);
  Tile& getTile(int row, int col);
  Tile& getTile(std::pair<int, int> coords);
  std::map<std::pair<int, int>, Tile>& get_all_tiles();

  int getRows();
  int getCols();

 private:
  std::pair<int, int> size;
  std::map<std::pair<int, int>, Tile> tiles;
};

#endif // THE_SHINING_GAME_PROJECT_237_BLOCK_H
