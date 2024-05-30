#pragma once
#include "constructions.h"
#include "utils/thread_pool.h"

#include <filesystem>
#include <unordered_map>
#include <unordered_set>

class Translation
{
  protected:
  ThreadPool pool;

  private:
  std::vector<std::string> files;
  std::unordered_map<std::string, unsigned char> custom_types;
  std::unordered_map<std::string, unsigned char> typedefs;
  std::unordered_map<std::string, std::unique_ptr<Func> > funcs;
  std::unordered_set<std::string> undefined_funcs;

  public:
  Translation(const Translation &)            = delete;
  Translation &operator=(const Translation &) = delete;
  explicit Translation(
      const std::string &filename,
      const std::vector<std::string> &,
      const std::vector<std::unordered_map<std::string, std::string> > &options
      = {});
};
