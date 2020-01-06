#include <string>

#include <Engine/DebugPrinter.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

#include <cmath>
#include <iostream>

#include "game.h"
/**
 *   @brief   Default Constructor.
 *   @details Consider setting the game's width and height
 *            and even seeding the random number generator.
 */
MyASGEGame::MyASGEGame()
{
  game_name = "ASGE Game";
}

/**
 *   @brief   Destructor.
 *   @details Remove any non-managed memory and callbacks.
 */
MyASGEGame::~MyASGEGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));

  this->inputs->unregisterCallback(
    static_cast<unsigned int>(mouse_callback_id));
}

/**
 *   @brief   Initialises the game.
 *   @details The game window is created and all assets required to
 *            run the game are loaded. The keyHandler and clickHandler
 *            callback should also be set in the initialise function.
 *   @return  True if the game initialised correctly.
 */
bool MyASGEGame::init()
{
  setupResolution();
  if (!initAPI())
  {
    return false;
  }

  // toggleFPS();

  // input handling functions
  inputs->use_threads = false;

  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &MyASGEGame::keyHandler, this);

  mouse_callback_id = inputs->addCallbackFnc(
    ASGE::E_MOUSE_CLICK, &MyASGEGame::clickHandler, this);

  setUpTiles();

  placeHolderPlayer();

  return true;
}

/**
 *   @brief   Sets the game window resolution
 *   @details This function is designed to create the window size, any
 *            aspect ratio scaling factors and safe zones to ensure the
 *            game frames when resolutions are changed in size.
 *   @return  void
 */
void MyASGEGame::setupResolution()
{
  // how will you calculate the game's resolution?
  // will it scale correctly in full screen? what AR will you use?
  // how will the game be framed in native 16:9 resolutions?
  // here are some arbitrary values for you to adjust as you see fit
  // https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/
  // Scaling_and_MultiResolution_in_2D_Games.php

  game_width = 1280;
  game_height = 720;
}

/**
 *   @brief   Processes any key inputs
 *   @details This function is added as a callback to handle the game's
 *            keyboard input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as
 *            you see fit.
 *   @param   data The event data relating to key input.
 *   @see     KeyEvent
 *   @return  void
 */
void MyASGEGame::keyHandler(ASGE::SharedEventData data)
{
  auto key = static_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
  bool pressed = true;
  if (key->action == ASGE::KEYS::KEY_RELEASED)
  {
    pressed = false;
  }

  switch (key->key)
  {
    case ASGE::KEYS::KEY_W:
    {
      W_PRESSED = pressed;
      break;
    }
    case ASGE::KEYS::KEY_S:
    {
      S_PRESSED = pressed;
      break;
    }
    case ASGE::KEYS::KEY_A:
    {
      A_PRESSED = pressed;
      break;
    }
    case ASGE::KEYS::KEY_D:
    {
      D_PRESSED = pressed;
      break;
    }
    default:
      break;
  }

  if (key->key == ASGE::KEYS::KEY_ENTER &&
      key->action == ASGE::KEYS::KEY_PRESSED)
  {
    follow_player = !follow_player;
  }
}

/**
 *   @brief   Processes any click inputs
 *   @details This function is added as a callback to handle the game's
 *            mouse button input. For this game, calls to this function
 *            are thread safe, so you may alter the game's state as you
 *            see fit.
 *   @param   data The event data relating to key input.
 *   @see     ClickEvent
 *   @return  void
 */
void MyASGEGame::clickHandler(ASGE::SharedEventData data)
{
  auto click = static_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;

  ASGE::DebugPrinter{} << "x_pos: " << x_pos << std::endl;
  ASGE::DebugPrinter{} << "y_pos: " << y_pos << std::endl;
  /*
    if(click->action == ASGE::MOUSE::BUTTON_PRESSED)
    {
      float x_offset = (game_width/2) - x_pos;
      float y_offset = (game_height/2) - y_pos;
      render_offset = Vector2(x_offset, y_offset);
      ASGE::DebugPrinter{} << "New offset: " << x_offset << "," << y_offset <<
    std::endl;
    }
    */
}

/**
 *   @brief   Updates the scene
 *   @details Prepares the renderer subsystem before drawing the
 *            current frame. Once the current frame is has finished
 *            the buffers are swapped accordingly and the image shown.
 *   @return  void
 */
void MyASGEGame::update(const ASGE::GameTime& game_time)
{
  // auto dt_sec = game_time.delta.count() / 1000.0;;
  // make sure you use delta time in any movement calculations!

  player->xPos(player->xPos() +
               (D_PRESSED - A_PRESSED) * game_time.delta.count() * 0.25f);
  player->yPos(player->yPos() +
               (S_PRESSED - W_PRESSED) * game_time.delta.count() * 0.25f);
  float x_offset = (game_width / 2) - player->xPos();
  float y_offset = (game_height / 2) - player->yPos();
  render_offset = Vector2(x_offset, y_offset);

  if (!in_menu)
  {
  }
}

/**
 *   @brief   Renders the scene
 *   @details Renders all the game objects to the current frame.
 *            Once the current frame is has finished the buffers are
 *            swapped accordingly and the image shown.
 *   @return  void
 */
void MyASGEGame::render(const ASGE::GameTime&)
{
  renderer->setFont(0);

  if (in_menu)
  {
    for (int i = 0; i < map_width; i++)
    {
      for (int j = 0; j < map_height; j++)
      {
        Block& block = map.at(std::pair<int, int>(i, j));
        for (int a = 0; a < block.getRows(); a++)
        {
          for (int b = 0; b < block.getCols(); b++)
          {
            renderSpriteWithOffset(block.getTile(a, b)->getSprite());
          }
        }
      }
    }
    renderSpriteWithOffset(player);
  }
}

void MyASGEGame::renderSpriteWithOffset(ASGE::Sprite* sprite)
{
  float old_xPos = sprite->xPos();
  float old_yPos = sprite->yPos();
  if (follow_player)
  {
    sprite->xPos(sprite->xPos() + render_offset.getX());
    sprite->yPos(sprite->yPos() + render_offset.getY());
  }
  renderer->renderSprite(*sprite);
  sprite->xPos(old_xPos);
  sprite->yPos(old_yPos);
}

void MyASGEGame::setUpTiles()
{
  for (int i = 0; i < map_width; i++)
  {
    for (int j = 0; j < map_height; j++)
    {
      map.emplace(std::pair<int, int>(i, j),
                  Block(tiles_per_block, tiles_per_block));
      Block& block = map.at(std::pair<int, int>(i, j));

      block.setPos(std::pair<float, float>(i * tiles_per_block * tile_size,
                                           j * tiles_per_block * tile_size));

      for (int a = 0; a < block.getRows(); a++)
      {
        for (int b = 0; b < block.getCols(); b++)
        {
          ASGE::Sprite* new_sprite;
          new_sprite = renderer->createRawSprite();
          block.getTile(a, b)->setSprite(new_sprite);
          ASGE::Sprite* tile_sprite = block.getTile(a, b)->getSprite();
          tile_sprite->loadTexture("/data/1px.png");
          tile_sprite->width(tile_size);
          tile_sprite->height(tile_size);
          tile_sprite->xPos(block.getXPos() + a * tile_size);
          tile_sprite->yPos(block.getYPos() + b * tile_size);
          if (block.getTile(a, b)->getIsWalkable())
          {
            tile_sprite->colour(ASGE::COLOURS::GREEN);
          }
        }
      }
    }
  }
}

void MyASGEGame::placeHolderPlayer()
{
  player = renderer->createRawSprite();
  player->xPos(5.f);
  player->yPos(5.f);
  player->loadTexture("/data/1px.png");
  player->colour(ASGE::COLOURS::RED);
  player->width(5);
  player->height(5);
}