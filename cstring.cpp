#include "cppstring.h"

String::String() : ptr_(nullptr), size_(0), capacity_(0) {
}

String::String(size_t size, char symbol) : ptr_(nullptr), size_(size), capacity_(size) {
  if (size == 0) {
    ptr_ = nullptr;
    return;
  }
  ptr_ = new char[size];
  for (size_t i = 0; i < size; ++i) {
    ptr_[i] = symbol;
  }
}

String::String(const char *str) : ptr_(nullptr), size_(std::strlen(str)), capacity_(size_) {  // NOLINT
  if (size_ == 0) {
    return;
  }
  ptr_ = new char[size_];
  std::strncpy(ptr_, str, size_);
}

String::String(const char *str, size_t len) : ptr_(nullptr), size_(len), capacity_(len) {
  if (size_ == 0) {
    return;
  }
  ptr_ = new char[len];
  std::strncpy(ptr_, str, len);
}

String::String(const String &str) : ptr_(nullptr), size_(str.Size()), capacity_(str.Capacity()) {  // NOLINT
  if (capacity_ == 0) {
    ptr_ = nullptr;
    size_ = 0;
    return;
  }
  ptr_ = new char[str.Capacity()];
  strncpy(ptr_, str.Data(), size_);
}

const char &String::operator[](size_t it) const {
  return ptr_[it];
}

char &String::operator[](size_t it) {
  return ptr_[it];
}

const char &String::At(size_t it) const {
  if (it >= size_) {
    throw StringOutOfRange{};
  }
  return ptr_[it];
}

char &String::At(size_t it) {
  if (it >= size_) {
    throw StringOutOfRange{};
  }
  return ptr_[it];
}

const char &String::Front() const {
  return At(0);
}

char &String::Front() {
  return At(0);
}

const char &String::Back() const {
  return At(size_ - 1);
}

char &String::Back() {
  return At(size_ - 1);
}

char *String::CStr() {
  return ptr_;
}

const char *String::CStr() const {
  return ptr_;
}

char *String::Data() {
  return ptr_;
}

const char *String::Data() const {
  return ptr_;
}

bool String::Empty() const {
  return (size_ == 0);
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String &other) {
  std::swap(ptr_, other.ptr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  --size_;
}

void String::PushBack(char symbol) {
  if (ptr_ == nullptr) {
    ptr_ = new char[1];
    ptr_[0] = symbol;
    capacity_ = 1;
    size_ = 1;
    return;
  }
  if (size_ == capacity_) {
    Reserve(2 * capacity_ + 2);
  }
  ptr_[size_] = symbol;
  ++size_;
}

String &String::operator=(const String &str) {
  if (str == *this) {
    return *this;
  }
  delete[] ptr_;
  if (str.Size() == 0) {
    capacity_ = 0;
    size_ = 0;
    ptr_ = nullptr;
    return *this;
  }
  size_ = str.Size();
  capacity_ = str.Capacity();
  ptr_ = new char[capacity_];
  std::strncpy(ptr_, str.Data(), str.Size());
  return *this;
}

String &String::operator+=(const String &str) {
  if (str.Data() == nullptr) {
    return *this;
  }
  if (str.Size() + size_ >= capacity_) {
    Reserve((str.Size() + size_) * 2 + 1);
  }
  std::strncpy(ptr_ + size_, str.Data(), str.Size());
  size_ += str.Size();
  return *this;
}

void String::Resize(size_t new_size, char symbol) {
  if (new_size > capacity_) {
    Reserve(new_size);
  }
  if (size_ < new_size) {
    std::memset(ptr_ + size_, symbol, new_size - size_);
  }
  size_ = new_size;
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }
  auto new_ptr = new char[new_capacity];
  std::strncpy(new_ptr, ptr_, size_);
  delete[] ptr_;
  ptr_ = new_ptr;
  capacity_ = new_capacity;
}

void String::ShrinkToFit() {
  if (capacity_ == size_) {
    return;
  }
  if (size_ == 0) {
    delete[] ptr_;
    ptr_ = nullptr;
    capacity_ = 0;
    return;
  }
  auto new_ptr = new char[size_];
  std::strncpy(new_ptr, ptr_, size_);
  delete[] ptr_;
  ptr_ = new_ptr;
  capacity_ = size_;
}

String operator+(const String &str_1, const String &str_2) {
  String result = str_1;
  result += str_2;
  return result;
}

bool operator<(const String &my, const String &other) {
  size_t len = std::min(my.Size(), other.Size());
  if (std::strncmp(my.Data(), other.Data(), len) == 0) {
    return my.Size() < other.Size();
  }
  return std::strncmp(my.Data(), other.Data(), len) < 0;
}

bool operator>(const String &my, const String &other) {
  size_t len = std::min(my.Size(), other.Size());
  if (std::strncmp(my.Data(), other.Data(), len) == 0) {
    return my.Size() > other.Size();
  }
  return std::strncmp(my.Data(), other.Data(), len) > 0;
}

bool operator<=(const String &my, const String &other) {
  return !(my > other);
}

bool operator>=(const String &my, const String &other) {
  return !(my < other);
}

bool operator==(const String &my, const String &other) {
  return (my.Size() == other.Size() && std::strncmp(my.Data(), other.Data(), my.Size()) == 0);
}

bool operator!=(const String &my, const String &other) {
  return !(my == other);
}

std::ostream &operator<<(std::ostream &os, String str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    os << str[i];
  }
  return os;
}

String::~String() {
  delete[] ptr_;
}
