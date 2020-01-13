//
// Created by e22-watson on 13/01/2020.
//

#include "GameObject.h"

bool GameObject::addSpriteComponent(std::unique_ptr<ASGE::Renderer>& renderer,
                                    const std::string& sprite_file)
{
  spriteComponent = new SpriteComponent(renderer, sprite_file);
}

ASGE::Sprite* GameObject::getSprite()
{
  return spriteComponent->getSprite();
}