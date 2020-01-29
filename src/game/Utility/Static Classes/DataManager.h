//
// Created by e22-watson on 29/01/2020.
//

#ifndef THE_SHINING_GAME_PROJECT_237_DATAMANAGER_H
#define THE_SHINING_GAME_PROJECT_237_DATAMANAGER_H
#include <Engine/FileIO.h>
#include <vector>

class DataManager
{
 public:
  static void unlockLoreByIndex(int id);
  static std::vector<bool> getAllUnlockedLore();
};

#endif // THE_SHINING_GAME_PROJECT_237_DATAMANAGER_H
