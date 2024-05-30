#include "ncurses.h"
#include "toml++/toml.h"
#include "translator/translation.h"
#include "utils/thread_pool.h"
#include "utils/todo.h"
#include "utils/dir_parser.h"
#include <format>
#include <iostream>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <cstdlib>

/*
__uint128_t
fact(__uint128_t a)
{
  if (a == 0)
    return 1;
  return a * fact(a - 1);
}
*/

int
main()
{
  std::string path = getPath();
  std::cout << "you are at the " << path << std::endl;

  bool isParsing = true;

  while (isParsing)
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



  //Translation a(path, std::vector<std::string>{ "p" });
  //todo();
}
