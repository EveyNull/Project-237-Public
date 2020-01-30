//
// Created by e22-watson on 29/01/2020.
//

#include "DataManager.h"
#include "../StringHelper.h"
#include <Engine/DebugPrinter.h>

void DataManager::unlockLoreByIndex(int id)
{
  ASGE::FILEIO::createDir("/userData/");

  std::vector<bool> current_data = getAllUnlockedLore();

  current_data[id] = true;
  ASGE::FILEIO::File file = ASGE::FILEIO::File();
  if (file.open("/userData/data", ASGE::FILEIO::File::IOMode::WRITE))
  {
    auto data = ASGE::FILEIO::IOBuffer();

    for (int value : current_data)
    {
      data.append(std::to_string(value) + '\n');
    }

    file.write(data);
    file.close();
  }
  else
  {
    ASGE::DebugPrinter{} << "Failed!" << std::endl;
  }
}

std::vector<bool> DataManager::getAllUnlockedLore()
{
  std::vector<bool> results;
  ASGE::FILEIO::File file;
  if (file.open("/userData/data", ASGE::FILEIO::File::IOMode::READ))
  {
    auto buffer = file.read();
    std::vector<std::string> lines =
      StringHelper::split(buffer.as_char(), "\n");
    for (const std::string& line : lines)
    {
      results.push_back(std::stoi(line));
    }
    file.close();
  }
  else
  {
    results = std::vector<bool>(5);
  }
  return results;
}