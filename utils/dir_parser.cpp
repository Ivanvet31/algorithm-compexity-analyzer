#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

#include "dir_parser.h"

void printVec(const std::vector<std::string> &vec)
{
  int it = 0;
  for (const auto &x : vec)
    {
      std::cout << it << " -> " << x << '\n';
      ++it;
    }
}

std::string getPath()
{
    return std::filesystem::current_path();
}

std::vector<std::string> getDirs(const std::string &path)
{
  std::string back = path;

  while (back.back() != '/')
    {
      back.pop_back();
    }

  back.pop_back();
  std::vector<std::string> dirs = {back};

  for (const std::filesystem::directory_entry &dir : std::filesystem::directory_iterator(path))
    {
      dirs.push_back(dir.path().string());
    }

  return dirs;
}
