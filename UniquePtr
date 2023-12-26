#pragma once

template <class T>
class UniquePtr {
  T *ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T *ptr) noexcept : ptr_(ptr) {
  }
  UniquePtr(UniquePtr<T> &&ptr) noexcept : ptr_(ptr.ptr_) {
    ptr.ptr_ = nullptr;
  }
  UniquePtr(const UniquePtr<T> &ptr) = delete;

  UniquePtr<T> &operator=(const UniquePtr<T> &ptr) = delete;
  UniquePtr<T> &operator=(UniquePtr<T> &&ptr) noexcept {
    if (&ptr != this) {
      delete ptr_;
      ptr_ = ptr.ptr_;
      ptr.ptr_ = nullptr;
    }
    return *this;
  }

  T *Release() {
    T *raw_ptr = ptr_;
    ptr_ = nullptr;
    return raw_ptr;
  }

  void Reset(T *ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void Swap(UniquePtr<T> &ptr) noexcept {
    std::swap(ptr_, ptr.ptr_);
  }

  T *Get() const {
    return ptr_;
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_;
  }

  ~UniquePtr() {
    delete ptr_;
  }
};
