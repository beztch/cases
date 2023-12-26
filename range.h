#pragma once

#define REVERSE_RANGE_IMPLEMENTED

class Range {
 private:
  int begin_;
  int end_;
  int step_;

 public:
  Range(const int begin, const int end, const int step) : begin_(begin), end_(end), step_(step) {
  }
  Range(const int begin, const int end) : begin_(begin), end_(end), step_(1) {
  }
  explicit Range(const int end) : begin_(0), end_(end), step_(1) {
  }

  class Iterator {
   private:
    int value_;
    int step_;

   public:
    Iterator(int value, int step) : value_(value), step_(step) {
    }
    int operator*() const {
      return value_;
    }
    Iterator& operator++() {
      value_ += step_;
      return *this;
    }
    Iterator operator++(int) {
      value_ += step_;
      return *this;
    }
    bool operator!=(const Iterator& other) const {
      return ((step_ > 0 && value_ < other.value_) || (step_ < 0 && value_ > other.value_)) && (step_ != 0);
    }
  };

  class RIterator {
   private:
    int value_;
    int step_;

   public:
    RIterator(int value, int step) : value_(value), step_(step) {
    }
    int operator*() const {
      return value_;
    }
    RIterator& operator++() {
      value_ -= step_;
      return *this;
    }
    RIterator operator++(int) {
      value_ -= step_;
      return *this;
    }
    bool operator!=(const RIterator& other) const {
      return ((step_ > 0 && value_ >= other.value_) || (step_ < 0 && value_ <= other.value_)) && (step_ != 0);
    }
  };

  Iterator begin() const {  // NOLINT
    return Iterator(begin_, step_);
  }

  RIterator rbegin() const {  // NOLINT
    if (step_ > 0 && (end_ - begin_) % step_ != 0) {
      return RIterator(begin_ + (end_ - begin_ + step_ - 1) / step_ * step_ - step_, step_);
    }
    if (step_ < 0 && (end_ - begin_) % (-step_) != 0) {
      return RIterator(begin_ + (end_ - begin_ + step_ - 1) / step_ * step_ - step_, step_);
    }
    if (step_ > 0 && (end_ - begin_) % step_ == 0) {
      return RIterator(end_ - step_, step_);
    }
    if (step_ < 0 && (end_ - begin_) % (-step_) == 0) {
      return RIterator(end_ - step_, step_);
    }
    return RIterator(begin_, step_);
  }

  RIterator rend() const {  // NOLINT
    return RIterator(begin_, step_);
  }

  Iterator end() const {  // NOLINT
    return Iterator(end_, step_);
  }
};
