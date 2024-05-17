#pragma once

#include <mutex>

template <typename T> class Singleton
{
  private:
  static T *instance;
  static std::mutex mutex;

  protected:
  Singleton()                             = default;
  ~Singleton()                            = default;
  Singleton(const Singleton &)            = delete;
  Singleton &operator=(const Singleton &) = delete;

  public:
  static T *
  get_instance()
  {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
      instance = new T();
    return instance;
  }

  static void
  destroy_instance()
  {
    delete instance;
    instance = nullptr;
  }
};

template <typename T> T *Singleton<T>::instance = nullptr;

template <typename T> std::mutex Singleton<T>::mutex;
