# pragma once
#include <iostream>
#include <cstring>
#include <cstdint>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char *ptr_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  String(size_t, char);
  String(const char *);  // NOLINT
  String(const char *, size_t);
  String(const String &);  // NOLINT
  const char &operator[](size_t) const;
  char &operator[](size_t);
  const char &At(size_t) const;
  char &At(size_t);
  const char &Front() const;
  char &Front();
  const char &Back() const;
  char &Back();
  char *CStr();
  const char *CStr() const;
  char *Data();
  const char *Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String &);
  void PopBack();
  void PushBack(char);
  String &operator=(const String &);
  String &operator+=(const String &);
  void Resize(size_t, char);
  void Reserve(size_t);
  void ShrinkToFit();
  friend String operator+(const String &, const String &);
  friend std::ostream &operator<<(std::ostream &, String);
  ~String();
};

bool operator<(const String &, const String &);
bool operator>(const String &, const String &);
bool operator<=(const String &, const String &);
bool operator>=(const String &, const String &);
bool operator==(const String &, const String &);
bool operator!=(const String &, const String &);
