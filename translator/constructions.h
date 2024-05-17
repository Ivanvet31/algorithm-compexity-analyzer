#pragma once
#include "basic.h"

#include <filesystem>
#include <memory>
#include <vector>

class Func
{
  std::vector<std::shared_ptr<Object>> content;
  std::filesystem::path source;
public:
  Func(const Func &)            = delete;
  Func &operator=(const Func &) = delete;
  auto &get_content() { return content; }
  void push_back(auto a) { content.push_back(std::make_shared<Object>(a)); }
};
