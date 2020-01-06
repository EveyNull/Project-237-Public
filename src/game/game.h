#pragma once
#include <Engine/OGLGame.h>
#include <map>
#include <string>

#include "Mapping/Block.h"

/**
 *  An OpenGL Game based on ASGE.
 */
class MyASGEGame : public ASGE::OGLGame
{
 public:
  MyASGEGame();
  ~MyASGEGame() final;
  bool init() override;

  void renderSpriteWithOffset(ASGE::Sprite* sprite);

  void setUpTiles();
  void placeHolderPlayer();

 private:
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void setupResolution();

  void update(const ASGE::GameTime&) override;
  void render(const ASGE::GameTime&) override;

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */
  bool in_menu = true;

  std::map<std::pair<int, int>, Block> map;

  int map_width = 10;
  int map_height = 5;

  int tiles_per_block = 10;
  int tile_size = 10;

  Vector2 render_offset = Vector2(0, 0);

  ASGE::Sprite* player = nullptr;

  bool W_PRESSED = false;
  bool S_PRESSED = false;
  bool A_PRESSED = false;
  bool D_PRESSED = false;

  bool follow_player = true;
};