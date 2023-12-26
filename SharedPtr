#include <stdexcept>
#pragma once
#include <numeric>
#define WEAK_PTR_IMPLEMENTED

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class SharedPtr;
template <class T>
class WeakPtr;

struct Counter {
  size_t strong_counter;
  size_t weak_counter;
  Counter(size_t s, size_t w) {
    strong_counter = s;
    weak_counter = w;
  }
  void MoreStrong() {
    ++strong_counter;
  }
  void LessStrong() {
    --strong_counter;
  }
  void MoreWeak() {
    ++weak_counter;
  }
  void LessWeak() {
    --weak_counter;
  }
};

template <class T>
class SharedPtr {
  T *ptr_;
  Counter *count_;
  friend class WeakPtr<T>;

 public:
  SharedPtr() : ptr_(nullptr) {
    count_ = new Counter(1, 0);
  }
  SharedPtr(T *ptr) : ptr_(ptr) {  // NOLINT
    count_ = new Counter(1, 0);
  }
  SharedPtr(const SharedPtr<T> &ptr) : ptr_(ptr.ptr_), count_(ptr.count_) {
    if (count_ != nullptr) {
      count_->MoreStrong();
    }
  }
  SharedPtr(SharedPtr<T> &&ptr) noexcept {
    ptr_ = ptr.ptr_;
    count_ = ptr.count_;
    ptr.count_ = nullptr;
    ptr.ptr_ = nullptr;
  }
  SharedPtr(const WeakPtr<T> &ptr) {  // NOLINT
    if (ptr.Expired()) {
      throw BadWeakPtr{};
    }
    ptr_ = ptr.ptr_;
    if (ptr.count_ != nullptr) {
      count_ = ptr.count_;
      count_->MoreStrong();
    } else {
      count_ = nullptr;
    }
  }

  SharedPtr<T> &operator=(const SharedPtr<T> &ptr) {
    if (ptr_ == ptr.ptr_) {
      return *this;
    }
    if (count_ != nullptr) {
      count_->LessStrong();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
    ptr_ = ptr.ptr_;
    count_ = ptr.count_;
    if (count_ != nullptr) {
      count_->MoreStrong();
    }
    return *this;
  }

  SharedPtr<T> &operator=(SharedPtr<T> &&ptr) noexcept {
    if (&ptr != this) {
      if (count_ != nullptr) {
        count_->LessStrong();
        if (count_->strong_counter == 0) {
          delete ptr_;
          if (count_->weak_counter == 0) {
            delete count_;
          }
        }
      }
      ptr_ = ptr.ptr_;
      count_ = ptr.count_;
      ptr.ptr_ = nullptr;
      ptr.count_ = nullptr;
    }
    return *this;
  }

  void Reset(T *ptr = nullptr) {
    if (count_ != nullptr) {
      count_->LessStrong();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
    ptr_ = ptr;
    count_ = new Counter(1, 0);
  }

  void Swap(SharedPtr<T> &ptr) noexcept {
    std::swap(ptr_, ptr.ptr_);
    std::swap(count_, ptr.count_);
  }

  T *Get() const {
    return ptr_;
  }

  size_t UseCount() const {
    if (ptr_ == nullptr) {
      return 0;
    }
    return count_->strong_counter;
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  ~SharedPtr() {
    if (count_ != nullptr) {
      count_->LessStrong();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
  }
};

template <class T>
class WeakPtr {
  T *ptr_;
  Counter *count_;
  friend class SharedPtr<T>;

 public:
  WeakPtr() : ptr_(nullptr) {
    count_ = new Counter(0, 1);
  }
  WeakPtr(T *ptr) : ptr_(ptr) {  // NOLINT
    count_ = new Counter(0, 1);
  }
  WeakPtr(const WeakPtr<T> &ptr) : ptr_(ptr.ptr_), count_(ptr.count_) {
    if (count_ == nullptr) {
      return;
    }
    count_->MoreWeak();
  }
  WeakPtr(const SharedPtr<T> &ptr) : ptr_(ptr.ptr_), count_(ptr.count_) {  // NOLINT
    if (count_ == nullptr) {
      return;
    }
    count_->MoreWeak();
  }
  WeakPtr(WeakPtr<T> &&ptr) noexcept {  // NOLINT
    ptr_ = ptr.ptr_;
    count_ = ptr.count_;
    ptr.ptr_ = nullptr;
    ptr.count_ = nullptr;
  }

  WeakPtr &operator=(const WeakPtr<T> &ptr) {
    if (ptr_ == ptr.ptr_) {
      return *this;
    }
    if (count_ != nullptr) {
      count_->LessWeak();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
    ptr_ = ptr.ptr_;
    count_ = ptr.count_;
    if (count_ != nullptr) {
      count_->MoreWeak();
    }
    return *this;
  }
  WeakPtr &operator=(WeakPtr<T> &&ptr) noexcept {
    if (ptr_ == ptr.ptr_) {
      return *this;
    }
    if (count_ != nullptr) {
      count_->LessWeak();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
    ptr_ = ptr.ptr_;
    count_ = ptr.count_;
    ptr.ptr_ = nullptr;
    ptr.count_ = nullptr;
    return *this;
  }

  void Reset(T *ptr = nullptr) {
    if (count_ != nullptr) {
      count_->LessWeak();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
    ptr_ = ptr;
    count_ = new Counter(0, 1);
  }
  void Swap(WeakPtr<T> &ptr) noexcept {
    std::swap(ptr_, ptr.ptr_);
    std::swap(count_, ptr.count_);
  }
  T *Get() const {
    return ptr_;
  }
  size_t UseCount() const {
    if (ptr_ == nullptr) {
      return 0;
    }
    return count_->strong_counter;
  }
  bool Expired() const {
    return (ptr_ == nullptr || count_ == nullptr || count_->strong_counter == 0);
  }
  SharedPtr<T> Lock() const {
    if (Expired()) {
      return nullptr;
    }
    return SharedPtr<T>(*this);
  }
  T &operator*() const {
    return *(ptr_);
  }
  T *operator->() const {
    return ptr_;
  }
  explicit operator bool() const {
    return ptr_ != nullptr;
  }
  ~WeakPtr() {
    if (count_ != nullptr) {
      count_->LessWeak();
      if (count_->strong_counter == 0) {
        delete ptr_;
        if (count_->weak_counter == 0) {
          delete count_;
        }
      }
    }
  }
};
