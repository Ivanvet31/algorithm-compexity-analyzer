#pragma once
#include "utils/types.h"
#include "translator/basic.h"
#include <format>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Constant : Object
{
  std::string content{};

  public:
  Constant(const Constant &)            = delete;
  Constant &operator=(const Constant &) = delete;
  [[nodiscard]] std::string
  get_content() const
  {
    return content;
  }
};

template <> struct std::formatter<Constant> : std::formatter<std::string>
{
  auto
  format(const Constant &p, std::format_context &ctx)
  {
    return formatter<std::string>::format("<Constant>", ctx);
  }
};

class Constants : Object
{
  std::vector<const Constant *> constants;

  public:
  Constants(const Constants &)            = delete;
  Constants &operator=(const Constants &) = delete;
  Constants &
  operator+=(const Constant *a)
  {
    constants.push_back(a);
    return *this;
  }
  [[nodiscard]] std::vector<const Constant *>
  get_constants() const
  {
    return constants;
  };
};

template <> struct std::formatter<Constants> : std::formatter<std::string>
{
  auto
  format(const Constants &p, std::format_context &ctx)
  {
    std::string conc_str;
    for (auto i = 0; i < p.get_constants().size(); ++i)
      conc_str += std::format("<Const{}>", i);
    return formatter<std::string>::format(conc_str, ctx);
  }
};

class AbstractList : Object
{
  size_t exp_size;
  u8 memory : 3 = 0;

  public:
  AbstractList(const AbstractList &)            = delete;
  AbstractList &operator=(const AbstractList &) = delete;
  explicit AbstractList(const size_t a, const u8 mem) : exp_size(a), memory(mem){};
};

template <> struct std::formatter<AbstractList> : std::formatter<std::string>
{
  auto
  format(const AbstractList &p, std::format_context &ctx)
  {
    return formatter<std::string>::format("<AbstractList>", ctx);
  }
};

class String : Object
{
  std::string content;

  public:
  String(const String &)            = delete;
  String &operator=(const String &) = delete;
  explicit String(std::string a) : content(std::move(a)){};
  std::string &get_content() { return content; }
};

template <> struct std::formatter<String> : std::formatter<std::string>
{
  auto
  format(const String &p, std::format_context &ctx)
  {
    return formatter<std::string>::format("<String>", ctx);
  }
};
