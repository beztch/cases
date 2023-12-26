#include "string_view.h"

StringView::StringView() : size_(0), sv_(nullptr) {
}

StringView::StringView(const char *string) {  // NOLINT
  sv_ = string;
  size_ = 0;
  while (*(string++) != '\0') {
    ++size_;
  }
}

StringView::StringView(const char *string, size_t size) : size_(size), sv_(string) {
}

const char &StringView::operator[](size_t t) {
  return sv_[t];
}

const char &StringView::operator[](size_t t) const {
  return sv_[t];
}

const char &StringView::At(size_t idx) {
  if (idx >= size_) {
    throw StringViewOutOfRange{};
  }
  return sv_[idx];
}

const char &StringView::At(size_t idx) const {
  if (idx >= size_) {
    throw StringViewOutOfRange{};
  }
  return sv_[idx];
}

const char &StringView::Front() {
  return sv_[0];
}

const char &StringView::Front() const {
  return sv_[0];
}

const char &StringView::Back() {
  return sv_[size_ - 1];
}

const char &StringView::Back() const {
  return sv_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return (size_ == 0);
}

const char *StringView::Data() const {
  return sv_;
}

void StringView::Swap(StringView &chel) {
  size_t tmp_size = chel.Size();
  const char *tmp_sv = chel.Data();
  chel.size_ = size_;
  chel.sv_ = sv_;
  sv_ = tmp_sv;
  size_ = tmp_size;
}

void StringView::RemovePrefix(size_t prefix_size) {
  sv_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (pos >= size_) {
    throw StringViewOutOfRange{};
    return StringView(sv_, 1);
  }
  size_t kik = std::min(size_ - pos, count);
  return StringView(sv_ + pos, kik);
}
