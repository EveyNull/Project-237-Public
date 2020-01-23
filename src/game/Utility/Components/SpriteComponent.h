//
// Created by e22-watson on 13/01/2020.
//

#include "Rect.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

#ifndef THE_SHINING_GAME_PROJECT_237_SPRITECOMPONENT_H
#  define THE_SHINING_GAME_PROJECT_237_SPRITECOMPONENT_H

class SpriteComponent
{
 public:
  SpriteComponent() = default;
  SpriteComponent(ASGE::Renderer* renderer,
                  const std::string& sprite_file,
                  float& tile_size);
  ASGE::Sprite* getSprite();
  void setVisible(bool vis);
  bool getVisible();

  rect getBoundingBox() const;

 private:
  ASGE::Sprite* sprite = nullptr;
  bool visible = true;
};

#endif // THE_SHINING_GAME_PROJECT_237_SPRITECOMPONENT_H
