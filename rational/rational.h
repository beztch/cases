#pragma once
#include <numeric>
#include <iostream>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

int GCD(int, int);

class Rational {
 private:
  int num_;
  uint denum_;
  friend std::ostream& operator<<(std::ostream&, Rational);
  friend std::istream& operator>>(std::istream&, Rational&);
  friend Rational operator+(Rational p, Rational r);
  friend Rational operator-(Rational p, Rational r);
  friend Rational operator/(Rational p, Rational r);
  friend Rational operator*(Rational p, Rational r);
  friend bool operator<(Rational p, Rational r);
  friend bool operator>(Rational p, Rational r);
  friend bool operator<=(Rational p, Rational r);
  friend bool operator>=(Rational p, Rational r);
  friend bool operator==(Rational p, Rational r);
  friend bool operator!=(Rational p, Rational r);

  void Reduc(int64_t a, int64_t b);

 public:
  Rational();

  Rational(int n);  // NOLINT

  Rational(int64_t a, int64_t b);

  int GetNumerator() const;

  uint GetDenominator() const;

  void SetNumerator(int64_t a);

  void SetDenominator(int64_t b);

  Rational& operator+=(Rational r);

  Rational& operator-=(Rational r);

  Rational& operator/=(Rational r);

  Rational& operator*=(Rational r);

  Rational operator+() const;

  Rational operator-() const;

  Rational& operator++();

  Rational& operator--();

  Rational operator++(int);

  Rational operator--(int);
};

Rational operator+(Rational p, Rational r);

Rational operator-(Rational p, Rational r);

Rational operator/(Rational p, Rational r);

Rational operator*(Rational p, Rational r);

bool operator<(Rational p, Rational r);

bool operator>(Rational p, Rational r);

bool operator<=(Rational p, Rational r);

bool operator>=(Rational p, Rational r);

bool operator==(Rational p, Rational r);

bool operator!=(Rational p, Rational r);

std::ostream& operator<<(std::ostream& os, Rational value);

std::istream& operator>>(std::istream& is, Rational& value);
