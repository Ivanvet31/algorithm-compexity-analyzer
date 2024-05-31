#include "ncurses.h"
#include "toml++/toml.h"
#include "translator/translation.h"
#include "utils/dir_parser.h"
#include "utils/thread_pool.h"
#include "utils/todo.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

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
  char ch;

  std::string path = dir_parser::getPath();

  path = dir_parser::browseFiles(path);
  Translation algo(path, std::vector<std::string>{ "p" });

  /*int it = 1;
  for (const auto &f : algo.getFuncs())
    {
      std::cout << "the " << it << " func" << " \n=============================\n" << f << "\n";
      ++it;
    }*/

  algo.getComplexity();

  for (int i = 0; i < algo.getSize(); ++i)
    {
      std::cout << "func 1: \n\t" << algo.getComplexity(i) << '\n';
    }


  //todo();
}
