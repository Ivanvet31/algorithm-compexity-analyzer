#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

#include "dir_parser.h"

void dir_parser::printVec(const std::vector<std::string> &vec)
{
  int it = 0;
  for (const auto &x : vec)
    {
      std::cout << it << " -> " << x << '\n';
      ++it;
    }
}

std::string dir_parser::getPath()
{
    return std::filesystem::current_path();
}

std::vector<std::string> dir_parser::getDirs(const std::string &path)
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

std::string dir_parser::browseFiles(const std::string &_path)
{
  std::string path = _path;
  std::cout << "you are at the " << path << std::endl;
  std::error_code err;
  bool isParsing = true;

  while (isParsing && std::filesystem::is_directory(path, err))
    {
      std::vector<std::string> dirs = getDirs(path);
      printVec(dirs);

      std::string x;
      std::cin >> x;

      if (x != "q" && stoi(x) > dirs.size())
        {
          std::cout << "Неверный формат входных данных!\n";
          continue;
        }

      if (x != "q")
        {
          path = dirs[stoi(x)];
        }
      else
        {
          isParsing = false;
        }

      std::system("clear");
    }

  return path;
}
