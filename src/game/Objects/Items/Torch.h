//
// Created by Kirsten on 14/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_TORCH_H
#define THE_SHINING_GAME_PROJECT_237_TORCH_H

<<<<<<< refs/remotes/origin/development:src/game/Objects/Items/Torch.h
#include "../../Utility/UI/ItemIDs.h"
#include "../GameObject.h"
#include "Item.h"
=======
#include "../Utility/ItemIDs.h"
#include "GameObject.h"
#include "item.h"
>>>>>>> Items - bottles work, UI fix, minor AI fix:src/game/Objects/Torch.h

class Torch : public Item
{
 public:
  Torch(ASGE::Renderer* renderer, int tile_size);
  void update(int tile_size, int frame, float delta_time) override;
  void changeFrame(int frame_number);

 private:
  std::string Frame1 = "/data/item_images/torchOn1.png";
  std::string Frame2 = "/data/item_images/torchOn2.png";
  std::string Frame3 = "/data/item_images/torchOn3.png";

  float timer = 0;
};

#endif // THE_SHINING_GAME_PROJECT_237_TORCH_H
