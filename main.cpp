#include "ncurses.h"
#include "parsing/pseudocodegen.cpp"
#include "toml++/toml.h"
#include "translator/translation.h"
#include "utils/thread_pool.h"
#include "utils/todo.h"
#include <format>
#include <iostream>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

__uint128_t
fact(__uint128_t a)
{
  if (a == 0)
    return 1;
  return a * fact(a - 1);
}

int
main()
{

  Translation a(std::vector<std::string>{"p"});
  todo();
}
