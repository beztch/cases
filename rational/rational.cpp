#include "rational.h"

int GCD(int64_t a, int64_t b) {
  if (a == 0 && b == 0) {
    return 0;
  }
  a = (a < 0 ? -a : a);
  b = (b < 0 ? -b : b);
  if (a == 0 || b == 0) {
    return (a + b > 0 ? a + b : -(a + b));
  }
  if (a < b) {
    return GCD(a, b - a);
  }
  if (b < a) {
    return GCD(a - b, b);
  }
  return a;
}

void Rational::Reduc(int64_t a, int64_t b) {
  if (b == 0) {
    throw RationalDivisionByZero{};
  }
  int64_t k = GCD(a, b);
  if (b > 0) {
    num_ = a / k;
    denum_ = b / k;
    return;
  }
  num_ = -a / k;
  denum_ = -b / k;
}

Rational::Rational() : num_(0), denum_(1) {
}

Rational::Rational(int n) : num_(n), denum_(1) {  //NOLINT
}

Rational::Rational(int64_t a, int64_t b) {
  Reduc(a, b);
}

int Rational::GetNumerator() const {
  return num_;
}

uint Rational::GetDenominator() const {
  return denum_;
}

void Rational::SetNumerator(int64_t a) {
  Reduc(a, denum_);
}

void Rational::SetDenominator(int64_t b) {
  Reduc(num_, b);
}

Rational operator+(Rational p, Rational r) {
  int64_t a = p.num_ * static_cast<int64_t>(r.denum_) + r.num_ * static_cast<int64_t>(p.denum_);
  int64_t b = static_cast<int64_t>(p.denum_) * r.denum_;
  Rational c(a, b);
  return c;
}

Rational operator-(Rational p, Rational r) {
  int64_t a = p.num_ * static_cast<int64_t>(r.denum_) - r.num_ * static_cast<int64_t>(p.denum_);
  int64_t b = static_cast<int64_t>(p.denum_) * r.denum_;
  Rational c(a, b);
  return c;
}

Rational operator/(Rational p, Rational r) {
  int64_t a = p.num_ * static_cast<int64_t>(r.denum_);
  int64_t b = static_cast<int64_t>(p.denum_) * r.num_;
  Rational c(a, b);
  return c;
}

Rational operator*(Rational p, Rational r) {
  int64_t a = static_cast<int64_t>(p.num_) * r.num_;
  int64_t b = static_cast<int64_t>(p.denum_) * r.denum_;
  Rational c(a, b);
  return c;
}

Rational& Rational::operator+=(Rational r) {
  int64_t a = num_ * static_cast<int64_t>(r.denum_) + r.num_ * static_cast<int64_t>(denum_);
  int64_t b = static_cast<int64_t>(denum_) * r.denum_;
  Reduc(a, b);
  return *this;
}

Rational& Rational::operator-=(Rational r) {
  int64_t a = num_ * static_cast<int64_t>(r.denum_) - r.num_ * static_cast<int64_t>(denum_);
  int64_t b = static_cast<int64_t>(denum_) * r.denum_;
  Reduc(a, b);
  return *this;
}

Rational& Rational::operator/=(Rational r) {
  int64_t a = num_ * static_cast<int64_t>(r.denum_);
  int64_t b = static_cast<int64_t>(denum_) * r.num_;
  Reduc(a, b);
  return *this;
}

Rational& Rational::operator*=(Rational r) {
  int64_t a = static_cast<int64_t>(num_) * r.num_;
  int64_t b = static_cast<int64_t>(denum_) * r.denum_;
  Reduc(a, b);
  return *this;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  Rational r(-num_, static_cast<int64_t>(denum_));
  return r;
}

Rational& Rational::operator++() {
  num_ += static_cast<int>(denum_);
  return *this;
}

Rational& Rational::operator--() {
  num_ -= static_cast<int>(denum_);
  return *this;
}

Rational Rational::operator++(int) {
  num_ += static_cast<int>(denum_);
  Rational c(num_ - static_cast<int>(denum_), static_cast<int>(denum_));
  return c;
}

Rational Rational::operator--(int) {
  num_ -= static_cast<int>(denum_);
  Rational c(num_ + static_cast<int>(denum_), static_cast<int>(denum_));
  return c;
}

bool operator<(Rational p, Rational r) {
  return (p.num_ * static_cast<int64_t>(r.denum_) < static_cast<int64_t>(p.denum_) * r.num_);
}

bool operator>(Rational p, Rational r) {
  return (p.num_ * static_cast<int64_t>(r.denum_) > static_cast<int64_t>(p.denum_) * r.num_);
}

bool operator<=(Rational p, Rational r) {
  return (p.num_ * static_cast<int64_t>(r.denum_) <= static_cast<int64_t>(p.denum_) * r.num_);
}

bool operator>=(Rational p, Rational r) {
  return (p.num_ * static_cast<int64_t>(r.denum_) >= static_cast<int64_t>(p.denum_) * r.num_);
}

bool operator==(Rational p, Rational r) {
  return (p.num_ == r.num_ && p.denum_ == r.denum_);
}

bool operator!=(Rational p, Rational r) {
  return (p.num_ != r.num_ || p.denum_ != r.denum_);
}

std::ostream& operator<<(std::ostream& os, Rational value) {
  if (value.denum_ == 1) {
    os << value.num_;
    return os;
  }
  os << value.num_ << "/" << value.denum_;
  return os;
}

std::istream& operator>>(std::istream& is, Rational& value) {
  int n, d;
  is >> n;
  char c = is.peek();
  if (c != '/') {
    value.num_ = n;
    value.denum_ = 1;
    return is;
  }
  is >> c;
  is >> d;
  value = Rational(n, d);
  return is;
}
