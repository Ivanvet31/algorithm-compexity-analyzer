#pragma once
#include "translator/basic.h"
#include "utils/types.h"
#include <format>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Constant : public virtual Object
{
  std::string content{};
  unsigned short mem_size : 3 = 0;

  public:
  [[nodiscard]] auto
  get_content() const
  {
    return content;
  }
  explicit
  Constant(std::string cont = "", const unsigned char mem = 1)
      : content(std::move(cont)), mem_size(mem)
  {
  }
  void
  show(std::ostream &out) const override
  {
    out << "<Constant: " << content << ':' << mem_size + 1 << '>' << std::endl;
  }
  void addContent(const std::shared_ptr<Object> &a) override {};
};

class Constants
{
  std::vector<std::shared_ptr<Constant> > constants{};

  public:
  Constants &
  operator+=(const std::shared_ptr<Constant> &a)
  {
    constants.push_back(a);
    return *this;
  }
  [[nodiscard]] std::vector<std::shared_ptr<Constant> >
  get_constants() const
  {
    return constants;
  };
  Constants() : constants() {}
  friend std::ostream &
  operator<<(std::ostream &out, const Constants &f)
  {
    for (const auto &a : f.constants)
      out << a;
    return out;
  }
};

class AbstractList : Object
{
  size_t exp_size;
  u8 memory : 3 = 0;

  public:
  AbstractList(const AbstractList &)            = delete;
  AbstractList &operator=(const AbstractList &) = delete;
  explicit AbstractList(const size_t a, const u8 mem)
      : exp_size(a), memory(mem){};
  friend std::ostream &
  operator<<(std::ostream &out, const AbstractList &f)
  {
    return out << "<AbstractList: " << f.exp_size << ':' << f.memory
               << std::endl;
  }
};

class String : Object
{
  std::string content;

  public:
  String(const String &)            = delete;
  String &operator=(const String &) = delete;
  explicit String(std::string a) : content(std::move(a)){};
  std::string &
  get_content()
  {
    return content;
  }
  friend std::ostream &
  operator<<(std::ostream &out, const String &f)
  {
    return out << "<String " << f.content << '>' << std::endl;
  }
};
