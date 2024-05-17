#pragma once

#include <format>
#include <stdexcept>

class NotImplementedException : public std::logic_error
{
  public:
  NotImplementedException() : std::logic_error("todo") {}
};

#define todo()                                                                \
  std::cerr << std::format("<{}> {}:{} ", __FILE__, __func__, __LINE__);      \
  throw NotImplementedException();
