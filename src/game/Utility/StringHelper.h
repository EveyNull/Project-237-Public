//
// Created by e22-watson on 13/01/2020.
//
#include <string>
#include <vector>

#ifndef THE_SHINING_GAME_PROJECT_237_STRINGHELPER_H
#  define THE_SHINING_GAME_PROJECT_237_STRINGHELPER_H

class StringHelper
{
 public:
  static std::vector<std::string>
  split(const std::string& string, std::string delimeter);
  static std::string join(const std::vector<std::string>& input);
};

#endif // THE_SHINING_GAME_PROJECT_237_STRINGHELPER_H
