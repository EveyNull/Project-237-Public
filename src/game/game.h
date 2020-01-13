#pragma once
#include <Engine/OGLGame.h>
#include <map>
#include <string>

#include "Objects/GameObject.h"
#include "Objects/Mapping/Block.h"
#include "Utility/SceneManager.h"
#include "Utility/Vector2.h"

/**
 *  An OpenGL Game based on ASGE.
 */
class MyASGEGame : public ASGE::OGLGame
{
 public:
  MyASGEGame();
  ~MyASGEGame() final;
  bool init() override;

 private:
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void setupResolution();

  void update(const ASGE::GameTime&) override;
  void render(const ASGE::GameTime&) override;

  int key_callback_id = -1;   /**< Key Input Callback ID. */
  int mouse_callback_id = -1; /**< Mouse Input Callback ID. */
  bool in_menu = true;

  SceneManager* sceneManager = nullptr;
};