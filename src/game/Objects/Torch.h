//
// Created by Kirsten on 14/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_TORCH_H
#define THE_SHINING_GAME_PROJECT_237_TORCH_H

#include "GameObject.h"
#include "item.h"

class Torch : public item
{
 public:
  void initialiseTorch(ASGE::Renderer* renderer,
                       int tileSize,
                       float xpos,
                       float ypos);
  void updateTorch(int tile_size, float delta_time);
  void changeFrame(int frame_number);

 private:
  std::string Frame1 = "/data/item_images/torchOn1.png";
  std::string Frame2 = "/data/item_images/torchOn2.png";
  std::string Frame3 = "/data/item_images/torchOn3.png";

  float timer = 0;
};

#endif // THE_SHINING_GAME_PROJECT_237_TORCH_H
