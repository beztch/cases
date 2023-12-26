#pragma once
#include <exception>
#include <memory>
#include <type_traits>

class BadOptionalAccess : public std::exception {
 public:
  const char *What() {
    return "lamba ili ferra";
  }
};

template <class T>
class Optional {
 private:
  std::aligned_storage<sizeof(T), alignof(T)> buffer_[sizeof(T)];
  bool alive_;

 public:
  Optional() : alive_(false) {
  }
  Optional(const Optional &other) : alive_(other.alive_) {
    if (alive_) {
      new (buffer_) T(*reinterpret_cast<const T *>(other.buffer_));
    }
  }
  Optional(Optional &&other) : alive_(other.alive_) {
    if (alive_) {
      new (buffer_) T(std::move(*reinterpret_cast<T *>(other.buffer_)));
    }
  }
  Optional(const T &value) : alive_(true) {  // NOLINT
    new (buffer_) T(*reinterpret_cast<const T *>(&value));
  }
  Optional(T &&value) : alive_(true) {  // NOLINT
    new (buffer_) T(std::move(*reinterpret_cast<T *>(&value)));
  }
  ~Optional() {
    if (alive_) {
      reinterpret_cast<T *>(buffer_)->~T();
      alive_ = false;
    }
  }
  Optional &operator=(const Optional &other) {
    if (this != &other) {
      if (alive_) {
        reinterpret_cast<T *>(buffer_)->~T();
      }
      if (!other.alive_) {
        alive_ = false;
      } else {
        alive_ = true;
        new (buffer_) T(*reinterpret_cast<const T *>(other.buffer_));
      }
    }
    return *this;
  }
  Optional &operator=(Optional &&other) {
    if (this != &other) {
      if (alive_) {
        reinterpret_cast<T *>(buffer_)->~T();
      }
      if (!other.alive_) {
        alive_ = false;
      } else {
        alive_ = true;
        new (buffer_) T(std::move(*reinterpret_cast<T *>(other.buffer_)));
      }
    }
    return *this;
  }
  Optional &operator=(const T &value) {
    if (alive_) {
      reinterpret_cast<T *>(buffer_)->~T();
    }
    alive_ = true;
    new (buffer_) T(*reinterpret_cast<const T *>(&value));
    return *this;
  }
  Optional &operator=(T &&value) {
    if (alive_) {
      reinterpret_cast<T *>(buffer_)->~T();
    }
    alive_ = true;
    new (buffer_) T(std::move(*reinterpret_cast<T *>(&value)));
    return *this;
  }
  bool HasValue() const {
    return alive_;
  }
  explicit operator bool() const {
    return alive_;
  }
  T &Value() {
    if (!alive_) {
      throw BadOptionalAccess{};
    }
    return *reinterpret_cast<T *>(buffer_);
  }
  const T Value() const {
    if (!alive_) {
      throw BadOptionalAccess{};
    }
    return *reinterpret_cast<const T *>(buffer_);
  }
  T &operator*() {
    return *reinterpret_cast<T *>(buffer_);
  }
  const T operator*() const {
    return *reinterpret_cast<const T *>(buffer_);
  }
  template <class... Args>
  T &Emplace(Args &&... args) {
    if (alive_) {
      reinterpret_cast<T *>(buffer_)->~T();
    }
    auto ptr = new (buffer_) T(std::forward<Args>(args)...);
    alive_ = true;
    return *ptr;
  }
  void Reset() {
    if (alive_) {
      reinterpret_cast<T *>(buffer_)->~T();
      alive_ = false;
    }
  }
  void Swap(Optional &other) {
    Optional tmp(std::move(other));
    other = *this;
    *this = tmp;
  }
};
