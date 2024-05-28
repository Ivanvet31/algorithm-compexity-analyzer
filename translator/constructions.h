#pragma once
#include "basic.h"
#include "types/types.h"

#include <filesystem>
#include <memory>
#include <utility>
#include <vector>


class Branch : public virtual Object
{
  std::vector<std::shared_ptr<Object> > content{};
  std::string inst{};
public:
  void
  addContent(const std::shared_ptr<Object> &obj) override
  {
    content.push_back(obj);
  }
  [[nodiscard]] auto
  get_content()
  {
    return content;
  }
  explicit Branch(std::string a) : inst(std::move(a)) {}
  void
  show(std::ostream &out) const override
  {
    out << "<Branch:" << inst << std::endl;
    for (const auto & a : content)
      out << "\t\t" << *a;
    out << '\t' <<  "</Branch>" << std::endl;
  }
  bool
  empty() { return content.empty(); }
  void
  clear() { content.clear(); }
  void set_name(std::string a) { inst = std::move(a); }
  Branch() = default;
};

class Func
{
  std::vector<std::shared_ptr<Object> > content{};
  std::string source;
  unsigned int return_mem_size : 3 = 0;
  size_t stack_mem                 = 0;
  Constants consts;

  public:
  void
  add_to_branch(const std::shared_ptr<Object>& obj)
  {
    content.back()->addContent(obj);
  }
  auto&
  get_content()
  {
    return content;
  }
  void
  push_back(auto a)
  {
    content.push_back(std::make_shared<Object>(a));
  }
  explicit Func(std::string sourc, const unsigned char mem = 1)
      : source(std::move(sourc)), return_mem_size(mem){};
  void
  expandStack(const size_t mem)
  {
    stack_mem += mem;
  }
  void
  addContent(const std::shared_ptr<Object> &obj)
  {
    content.push_back(obj);
  }
  void
  addConstant(const std::shared_ptr<Constant> &c)
  {
    consts += c;
  }
  friend std::ostream &
  operator<<(std::ostream &out, const Func &f)
  {
    out << "<Func:" << f.source << ':' << f.return_mem_size + 1 << ':'
        << f.stack_mem << std::endl;
    for (const auto &a : f.consts.get_constants())
      out << '\t' << *a;
    out << '>' << std::endl;
    size_t vl = 1;
    for (const auto &c : f.content)
      {
        for (auto i = 0; i < vl; ++i)
          out << '\t';
        out << *c;
      }
    return out << "</Func>\n" << std::endl;
  }
};
