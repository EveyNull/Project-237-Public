//
// Created by e22-watson on 20/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_PATHTILE_H
#  define THE_SHINING_GAME_PROJECT_237_PATHTILE_H

#endif // THE_SHINING_GAME_PROJECT_237_PATHTILE_H

struct PathTile
{
  std::pair<int, int> previous_coordinates;
  std::pair<int, int> coordinates;
  int step;
  int weight;
  PathTile(int n_step,
           int distance,
           const std::pair<int, int>& n_coordinates,
           const std::pair<int, int>& n_prev_coords) :
    coordinates(n_coordinates),
    previous_coordinates(n_prev_coords)
  {
    step = n_step;
    weight = distance + step;
  }
};