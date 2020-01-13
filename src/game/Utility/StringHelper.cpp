//
// Created by e22-watson on 13/01/2020.
//

#include "StringHelper.h"

std::vector<std::string>
StringHelper::split(const std::string& string, char delimiter)
{
  std::vector<std::string> results;
  std::size_t current, previous = 0;

  current = string.find(delimiter);
  while (current != std::string::npos)
  {
    results.emplace_back(string.substr(previous, current - previous));
    previous = current + 1;
    current = string.find(delimiter, previous);
  }
  return results;
}