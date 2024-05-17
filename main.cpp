#include "parsing/pseudocodegen.cpp"
#include "utils/thread_pool.h"
#include "utils/todo.h"
#include <format>
#include <iostream>
#include "toml++/toml.h"
#include "ncurses.h"

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
  read_file(
      "/home/kiberperdun/CLionProjects/algorithm-compexity-analyzer/test.c");
  ThreadPool pool(24);
  auto p      = new std::future<__uint128_t>[64];
  auto result = pool.enqueue([](int a) { return a * a; }, 509);
  std::cout << result.get();
  for (auto i = 2; i < 66; ++i)
    p[i - 2] = pool.enqueue(fact, i);
  for (auto i = 0; i < 64; ++i)
    std::cout << std::format("{}\n", p[i].get());
  delete[] p;
  todo();
}
