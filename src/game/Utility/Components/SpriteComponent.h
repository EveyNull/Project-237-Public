//
// Created by e22-watson on 13/01/2020.
//

#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

#ifndef THE_SHINING_GAME_PROJECT_237_SPRITECOMPONENT_H
#  define THE_SHINING_GAME_PROJECT_237_SPRITECOMPONENT_H

class SpriteComponent
{
 public:
  SpriteComponent() = default;
  SpriteComponent(std::unique_ptr<ASGE::Renderer>& renderer,
                  const std::string& sprite_file);
  ASGE::Sprite* getSprite();

 private:
  ASGE::Sprite* sprite = nullptr;
  bool visible;
};

#endif // THE_SHINING_GAME_PROJECT_237_SPRITECOMPONENT_H
