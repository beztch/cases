#pragma once
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 private:
  size_t size_;
  const char *sv_;

 public:
  StringView();

  StringView(const char *string);  // NOLINT

  StringView(const char *string, size_t size);

  const char &operator[](size_t t);

  const char &operator[](size_t t) const;

  const char &At(size_t idx);

  const char &At(size_t idx) const;

  const char &Front();

  const char &Front() const;

  const char &Back();

  const char &Back() const;

  size_t Size() const;

  size_t Length() const;

  bool Empty() const;

  const char *Data() const;

  void Swap(StringView &chel);

  void RemovePrefix(size_t prefix_size);

  void RemoveSuffix(size_t suffix_size);

  StringView Substr(size_t pos, size_t count);
};
