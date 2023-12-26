#pragma once
#include <iostream>
#include <iterator>
#include <exception>
#define VECTOR_MEMORY_IMPLEMENTED

template <class T>
class Vector {
 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T *buffer_ = nullptr;

 public:
  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<T *>;
  using ConstReverseIterator = std::reverse_iterator<const T *>;

  Vector() : size_(0), capacity_(0), buffer_(nullptr) {
  }
  explicit Vector(const size_t len) : size_(len), capacity_(len) {
    if (len > 0) {
      try {
        buffer_ = reinterpret_cast<T *>(::operator new(sizeof(T) * len));
      } catch (...) {
        buffer_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      try {
        std::uninitialized_default_construct(buffer_, buffer_ + len);
      } catch (...) {
        ::operator delete(buffer_);
        buffer_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }
  Vector(const size_t len, const T value) : size_(len), capacity_(len) {
    if (len > 0) {
      try {
        buffer_ = reinterpret_cast<T *>(::operator new(sizeof(T) * len));
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
        throw;
      }
      try {
        std::uninitialized_fill(buffer_, buffer_ + len, value);
      } catch (...) {
        ::operator delete(buffer_);
        throw;
      }
    }
  }
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator begin, Iterator end) : size_(std::distance(begin, end)), capacity_(size_) {
    if (size_ > 0) {
      try {
        buffer_ = reinterpret_cast<T *>(::operator new(sizeof(T) * size_));
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
        throw;
      }
      try {
        std::uninitialized_copy(begin, end, buffer_);
      } catch (...) {
        ::operator delete(buffer_);
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
        throw;
      }
    }
  }

  Vector(std::initializer_list<T> data) : size_(data.size()), capacity_(size_) {
    if (size_ > 0) {
      try {
        buffer_ = reinterpret_cast<T *>(::operator new(sizeof(T) * size_));
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
        throw;
      }
      try {
        std::uninitialized_copy(data.begin(), data.end(), buffer_);
      } catch (...) {
        ::operator delete(buffer_);
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
        throw;
      }
    }
  }

  Vector(const Vector &other) {
    if (other.capacity_ > 0) {
      buffer_ = reinterpret_cast<T *>(::operator new(sizeof(T) * other.capacity_));
      try {
        if (other.size_ > 0) {
          std::uninitialized_copy(other.buffer_, other.buffer_ + other.size_, buffer_);
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
      } catch (...) {
        ::operator delete(buffer_);
        buffer_ = nullptr;
        throw;
      }
    }
  }

  Vector(Vector &&other) noexcept : size_(other.size_), capacity_(other.capacity_), buffer_(other.buffer_) {
    other.buffer_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector &operator=(const Vector &other) {
    if (buffer_ != other.buffer_) {
      if (other.capacity_ != 0) {
        auto new_buffer = reinterpret_cast<T *>(::operator new(other.capacity_ * sizeof(T)));
        try {
          if (other.size_ > 0) {
            std::uninitialized_copy(other.buffer_, other.buffer_ + other.size_, new_buffer);
          }
          if (size_ > 0) {
            std::destroy(buffer_, buffer_ + size_);
          }
          if (capacity_ > 0) {
            ::operator delete(buffer_);
          }
          buffer_ = new_buffer;
          size_ = other.size_;
          capacity_ = other.capacity_;
        } catch (...) {
          ::operator delete(new_buffer);
          throw;
        }
      } else {
        if (size_ > 0) {
          std::destroy(buffer_, buffer_ + size_);
        }
        if (capacity_ > 0) {
          ::operator delete(buffer_);
        }
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
      }
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    if (buffer_ != other.buffer_) {
      if (size_ > 0) {
        std::destroy(buffer_, buffer_ + size_);
      }
      if (capacity_ > 0) {
        ::operator delete(buffer_);
      }
      buffer_ = other.buffer_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.buffer_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  const T *begin() const {  // NOLINT
    return static_cast<const T *>(buffer_);
  }

  T *begin() {  // NOLINT
    return static_cast<T *>(buffer_);
  }

  const T *end() const {  // NOLINT
    return static_cast<const T *>(buffer_ + size_);
  }

  T *end() {  // NOLINT
    return static_cast<T *>(buffer_ + size_);
  }

  const T *cbegin() {  // NOLINT
    return static_cast<const T *>(buffer_);
  }

  const T *cend() {  // NOLINT
    return static_cast<const T *>(buffer_ + size_);
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return static_cast<ConstReverseIterator>(buffer_ + size_);
  }

  ReverseIterator rbegin() {  // NOLINT
    return static_cast<ReverseIterator>(buffer_ + size_);
  }

  ConstReverseIterator rend() const {  // NOLINT
    return static_cast<ConstReverseIterator>(buffer_);
  }

  ReverseIterator rend() {  // NOLINT
    return static_cast<ReverseIterator>(buffer_);
  }

  ConstReverseIterator crbegin() {  // NOLINT
    return static_cast<ConstReverseIterator>(buffer_ + size_);
  }

  ConstReverseIterator crend() {  // NOLINT
    return static_cast<ConstReverseIterator>(buffer_);
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return (size_ == 0);
  }

  const T &operator[](size_t i) const {
    return *(buffer_ + i);
  }

  T &operator[](size_t i) {
    return *(buffer_ + i);
  }

  const T &At(size_t i) const {
    if (i >= size_) {
      throw std::out_of_range("fortinayti");
    }
    return *(buffer_ + i);
  }

  T &At(size_t i) {
    if (i >= size_) {
      throw std::out_of_range("babajy");
    }
    return *(buffer_ + i);
  }

  const T &Front() const {
    return *buffer_;
  }

  T &Front() {
    return *buffer_;
  }

  const T &Back() const {
    return *(buffer_ + size_ - 1);
  }

  T &Back() {
    return *(buffer_ + size_ - 1);
  }

  const T *Data() const {
    return buffer_;
  }

  T *Data() {
    return buffer_;
  }

  void Swap(Vector &other) {
    Vector<T> tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }

  void Resize(size_t new_size) {
    if (new_size > capacity_) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(std::max(new_size, capacity_) * sizeof(T)));
      try {
        if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
          std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
        } else {
          std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
        }
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      try {
        std::uninitialized_default_construct(new_buffer + size_, new_buffer + new_size);
        if (size_ > 0) {
          std::destroy(buffer_, buffer_ + size_);
        }
        if (capacity_ > 0) {
          ::operator delete(buffer_);
        }
        buffer_ = new_buffer;
        capacity_ = std::max(new_size, capacity_);
        size_ = new_size;
      } catch (...) {
        std::destroy(new_buffer, new_buffer + size_);
        ::operator delete(new_buffer);
        throw;
      }
    } else if (new_size < size_) {
      std::destroy(buffer_ + new_size, buffer_ + size_);
      size_ = new_size;
    } else if (new_size > size_) {
      std::uninitialized_default_construct(buffer_ + size_, buffer_ + new_size);
      size_ = new_size;
    }
  }

  void Resize(size_t new_size, T value) {
    if (new_size > capacity_) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(std::max(new_size, capacity_) * sizeof(T)));
      try {
        if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
          std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
        } else {
          std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
        }
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      try {
        std::uninitialized_fill(new_buffer + size_, new_buffer + new_size, value);
        if (size_ > 0) {
          std::destroy(buffer_, buffer_ + size_);
        }
        if (capacity_ > 0) {
          ::operator delete(buffer_);
        }
        buffer_ = new_buffer;
        capacity_ = std::max(new_size, capacity_);
        size_ = new_size;
      } catch (...) {
        std::destroy(new_buffer, new_buffer + size_);
        ::operator delete(new_buffer);
        throw;
      }
    } else if (new_size < size_) {
      std::destroy(buffer_ + new_size, buffer_ + size_);
      size_ = new_size;
    } else if (new_size > size_) {
      std::uninitialized_fill(buffer_ + size_, buffer_ + new_size, value);
      size_ = new_size;
    }
  }

  void Reserve(size_t new_cap) {
    if (capacity_ >= new_cap) {
      return;
    }
    auto new_buffer = reinterpret_cast<T *>(::operator new(new_cap * sizeof(T)));
    try {
      if (size_ > 0) {
        if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
          std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
        } else {
          std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
        }
      }
      capacity_ = new_cap;
      if (size_ > 0) {
        std::destroy(buffer_, buffer_ + size_);
      }
      if (capacity_ > 0) {
        ::operator delete(buffer_);
      }
      buffer_ = new_buffer;
    } catch (...) {
      ::operator delete(new_buffer);
      throw;
    }
  }

  void ShrinkToFit() {
    if (size_ == capacity_) {
      return;
    }
    if (size_ == 0) {
      this->Clear();
      return;
    }
    auto new_buffer = reinterpret_cast<T *>(::operator new(size_ * sizeof(T)));
    try {
      if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
        std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
      } else {
        std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
      }
    } catch (...) {
      ::operator delete(new_buffer);
      throw;
    }
    capacity_ = size_;
    if (size_ > 0) {
      std::destroy(buffer_, buffer_ + size_);
    }
    ::operator delete(buffer_);
    buffer_ = new_buffer;
  }

  void Clear() {
    if (size_ > 0) {
      std::destroy(buffer_, buffer_ + size_);
    }
    if (capacity_ > 0) {
      ::operator delete(buffer_);
    }
    size_ = 0;
    capacity_ = 0;
    buffer_ = nullptr;
  }

  void PushBack(const T &value) {
    if (capacity_ == 0) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(sizeof(T)));
      try {
        new (new_buffer) T(value);
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      buffer_ = new_buffer;
      size_ = 1;
      capacity_ = 1;
    } else if (size_ == capacity_) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(2 * capacity_ * sizeof(T)));
      try {
        if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
          std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
        } else {
          std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
        }
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      try {
        new (new_buffer + (size_)) T(value);
      } catch (...) {
        std::destroy(new_buffer, new_buffer + size_);
        ::operator delete(new_buffer);
        throw;
      }
      if (size_ > 0) {
        std::destroy(buffer_, buffer_ + size_);
      }
      if (capacity_ > 0) {
        ::operator delete(buffer_);
      }
      buffer_ = new_buffer;
      ++size_;
      capacity_ *= 2;
    } else {
      new (buffer_ + (size_)) T(value);
      ++size_;
    }
  }

  void PushBack(T &&value) {
    if (capacity_ == 0) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(sizeof(T)));
      try {
        new (new_buffer) T(std::move(value));
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      buffer_ = new_buffer;
      size_ = 1;
      capacity_ = 1;
    } else if (size_ == capacity_) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(2 * capacity_ * sizeof(T)));
      try {
        if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
          std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
        } else {
          std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
        }
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      try {
        new (new_buffer + (size_)) T(std::move(value));
      } catch (...) {
        std::destroy(new_buffer, new_buffer + size_);
        ::operator delete(new_buffer);
        throw;
      }
      if (size_ > 0) {
        std::destroy(buffer_, buffer_ + size_);
      }
      if (capacity_ > 0) {
        ::operator delete(buffer_);
      }
      buffer_ = new_buffer;
      ++size_;
      capacity_ *= 2;
    } else {
      new (buffer_ + (size_)) T(std::move(value));
      ++size_;
    }
  }

  template <class... Args>
  void EmplaceBack(Args &&... args) {
    if (capacity_ == 0) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(sizeof(T)));
      try {
        new (new_buffer + size_) T(std::forward<Args>(args)...);
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      ::operator delete(buffer_);
      buffer_ = new_buffer;
      capacity_ = size_ = 1;
    } else if (size_ + 1 > capacity_) {
      auto new_buffer = reinterpret_cast<T *>(::operator new(2 * (size_ + 1) * sizeof(T)));
      try {
        if constexpr (std::is_nothrow_move_constructible<T>::value) {  // NOLINT
          std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
        } else {
          std::uninitialized_copy(buffer_, buffer_ + size_, new_buffer);
        }
      } catch (...) {
        ::operator delete(new_buffer);
        throw;
      }
      try {
        new (new_buffer + size_) T(std::forward<Args>(args)...);
      } catch (...) {
        std::destroy(new_buffer, new_buffer + size_);
        ::operator delete(new_buffer);
        throw;
      }
      if (size_ > 0) {
        std::destroy(buffer_, buffer_ + size_);
      }
      if (capacity_ > 0) {
        ::operator delete(buffer_);
      }
      buffer_ = new_buffer;
      capacity_ = 2 * (size_ + 1);
      size_ += 1;
    } else {
      new (buffer_ + size_) T(std::forward<Args>(args)...);
      size_ += 1;
    }
  }

  void PopBack() {
    if (size_ > 0) {
      std::destroy_at(buffer_ + size_ - 1);
      --size_;
    }
  }

  ~Vector() noexcept {
    if (size_ > 0) {
      std::destroy(buffer_, buffer_ + size_);
    }
    if (capacity_ > 0) {
      ::operator delete(buffer_);
    }
    buffer_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
};

template <class T>
bool operator==(const Vector<T> &first, const Vector<T> &second) {
  if (first.Size() == second.Size()) {
    for (size_t i = 0; i < first.Size(); ++i) {
      if (first[i] != second[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

template <class T>
bool operator<(const Vector<T> &first, const Vector<T> &second) {
  size_t i = 0;
  size_t size_first = first.Size();
  size_t size_sec = second.Size();
  while (i < size_first && i < size_sec) {
    if (first[i] != second[i]) {
      return (first[i] < second[i]);
    }
    ++i;
  }
  return (size_first < size_sec);
}

template <class T>
bool operator>(const Vector<T> &first, const Vector<T> &second) {
  return !(first < second) && !(first == second);
}

template <class T>
bool operator<=(const Vector<T> &first, const Vector<T> &second) {
  return !(first > second);
}

template <class T>
bool operator>=(const Vector<T> &first, const Vector<T> &second) {
  return !(first < second);
}

template <class T>
bool operator!=(const Vector<T> &first, const Vector<T> &second) {
  return !(first == second);
}
