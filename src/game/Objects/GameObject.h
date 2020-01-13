//
// Created by e22-watson on 13/01/2020.
//

#include "../Utility/Components/SpriteComponent.h"
#include "../Utility/Vector2.h"

#ifndef THE_SHINING_GAME_PROJECT_237_GAMEOBJECT_H
#  define THE_SHINING_GAME_PROJECT_237_GAMEOBJECT_H

class GameObject
{
 public:
  GameObject() = default;
  ~GameObject() = default;
  bool addSpriteComponent(std::unique_ptr<ASGE::Renderer>& renderer,
                          const std::string& sprite_file);

  ASGE::Sprite* getSprite();

 private:
  Vector2 position = Vector2(0.f, 0.f);
  Vector2 rotation = Vector2(0.f, 0.f);
  SpriteComponent* spriteComponent = nullptr;
};

#endif // THE_SHINING_GAME_PROJECT_237_GAMEOBJECT_H
