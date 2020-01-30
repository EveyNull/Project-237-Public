//
// Created by e22-watson on 30/01/2020.
//

#include "LorePickup.h"

LorePickup::LorePickup(ASGE::Renderer* renderer,
                       int tile_size,
                       int n_lore_index) :
  item(renderer, tile_size)
{
  getSpriteComponent()->getSprite()->loadTexture("/data/item_images/"
                                                 "topgamer.png");
  spriteComponent->getSprite()->height(tile_size);
  spriteComponent->getSprite()->width(tile_size);
  item_id = ItemIDs::LORE_ITEM;
  lore_index = n_lore_index;
}

int LorePickup::getLoreIndex()
{
  return lore_index;
}