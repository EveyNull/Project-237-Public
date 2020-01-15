//
// Created by e22-watson on 06/12/2019.
//

#ifndef THE_SHINING_GAME_PROJECT_237_BLOCK_H
#define THE_SHINING_GAME_PROJECT_237_BLOCK_H

#include "../../Utility/Vector2.h"
#include "BlockType.h"
#include "Tile.h"
#include <map>

class Block
{
 public:
  Block(ASGE::Renderer* renderer,
        BlockType block_type,
        const std::pair<int, int>& n_size,
        float tile_size,
        const std::pair<int, int>& map_coords) :
    Block(renderer,
          BlockType::MIDDLE,
          n_size,
          tile_size,
          map_coords,
          false,
          false){};
  Block(ASGE::Renderer* renderer,
        BlockType block_type,
        const std::pair<int, int>& n_size,
        float tile_size,
        const std::pair<int, int>& map_coords,
        bool flip_x,
        bool flip_y);
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
