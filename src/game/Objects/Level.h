//
// Created by Tau on 15/01/2020.
//
#pragma once
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <vector>

#include "../Utility/AIManager.h"
#include "../Utility/MenuOption.h"

#include "../Utility/Scene.h"
#include "../Utility/SceneID.h"
#include "../Utility/UI.h"
#include "GameObject.h"
#include "Mapping/Block.h"
#include "Player.h"

#include "Barrier.h"
#include "BearTrap.h"
#include "Bottle.h"
#include "Torch.h"
#include "item.h"

#include "Enemy.h"
#include <Engine/FileIO.h>

#include <soloud.h>
#include <soloud_wav.h>

#ifndef PROJECT_LEVEL_H
#  define PROJECT_LEVEL_H

class Level : public Scene
{
 public:
  ~Level() = default;
  Level(const Level&) = default;
  Level& operator=(const Level&) = default;
  Level(ASGE::Renderer* renderer, MenuOption difficulty);
  bool setUpBlocks(ASGE::Renderer* renderer);

  item* pickItemForPlacing(ASGE::Renderer* renderer);
  bool setUpSounds();
  void loadWav(const std::string& path, SoLoud::Wav& sound);

  Direction updateFootprintDirection(const std::pair<int, int>& player_coords);

  SceneID update(float delta_time,
                 const std::deque<bool>& input_held,
                 const std::deque<bool>& input_release,
                 const ASGE::ClickEvent& click_event) override;
  Tile* getTileFromCoords(const std::pair<int, int>& target_pos);

  std::pair<int, int> getTileCoordsFromPos(GameObject* object);

  float horizontalMovement(float delta_time,
                           int horizontal,
                           std::pair<int, int> player_coords);
  float verticalMovement(float delta_time,
                         int vertical,
                         std::pair<int, int> player_coords);

  void render(ASGE::Renderer* renderer, Vector2 window_size);

  void renderAtOffset(ASGE::Renderer* renderer,
                      GameObject* gameObject,
                      bool render_from_center,
                      Vector2 window_size);

  void isEnemyOnItem();

  void makeGoop(ASGE::Renderer*);

 private:
  AIManager* ai_manager = nullptr;
  Player* player = nullptr;
  Enemy* enemy = nullptr;

  ASGE::Sprite* overlaymask = nullptr;

  std::map<std::pair<int, int>, Block> map;
  int tile_size = 100;
  bool game_over = false;

  GameObject* render_center = nullptr;

  int map_width = 0, map_height = 0, tiles_squared_per_block = 10;

  std::pair<int, int> player_last_tile = std::pair<int, int>(0, 0);

  int distance_in_array = 0;

  std::list<Item*> items;

  int spawn_beartraps = 10, spawn_bottles = 5, spawn_barriers = 5,
      spawn_torches = 5;

  // std::vector<BearTrap> beartraps;
  // std::vector<Torch> torches;
  // std::vector<Barrier> barriers;
  // std::vector<Bottle> bottles;
  // BearTrap* beartraps[20];
  // Torch* torches[20];
  // Barrier* barriers[20];
  // Bottle* bottles[20];
  std::vector<GameObject> goop;
  float goop_timer = 0;
  SoLoud::Soloud soloud;
  SoLoud::Wav angry_noises[4];
  SoLoud::Wav ambience;

  std::string ambient_track = "/data/sounds/ambient.wav";

  std::string sounds[4] = {
    "/data/sounds/angry_1.wav",
    "/data/sounds/angry_2.wav",
    "/data/sounds/angry_3.wav",
    "/data/sounds/angry_4.wav",
  };

  bool sound_enabled = false;

  bool paused = false;
};

#endif // PROJECT_LEVEL_H
