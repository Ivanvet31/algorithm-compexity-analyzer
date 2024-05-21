#pragma once
#include "basic.h"
#include "types/types.h"

#include <filesystem>
#include <memory>
#include <utility>
#include <vector>

class Func
{
  std::vector<std::shared_ptr<Object> > content;
  std::string source;
  unsigned int return_mem_size : 3 = 0;
  size_t stack_mem = 0;
  Constants consts;

  public:
  auto &
  get_content()
  {
    return content;
  }
  void
  push_back(auto a)
  {
    content.push_back(std::make_shared<Object>(a));
  }
  explicit Func(std::string sourc, const unsigned char mem = 1) : source(std::move(sourc)), return_mem_size(mem) {};
  void expandStack(const size_t mem) { stack_mem += mem; }
  void addConstant(const std::shared_ptr<Constant>& c) { consts += c; }
  friend std::ostream &operator<<(std::ostream &out, const Func &f)
  {
    out << "<Func:" << f.source << ':' << f.return_mem_size + 1 << ':' << f.stack_mem << std::endl;
    for (const auto & a : f.consts.get_constants())
      out << '\t' << *a;
    return out << '>' << std::endl << std::endl;
  }
};
