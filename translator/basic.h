#pragma once
#include <any>
#include <iostream>
#include <memory>

class Object
{
  public:
  virtual ~Object() = default;
  virtual void show(std::ostream &os) const = 0;
  virtual void addContent(const std::shared_ptr<Object> &) = 0;
  friend std::ostream &operator<<(std::ostream &out, const Object &obj)
  {
    obj.show(out);
    return out;
  }
};
