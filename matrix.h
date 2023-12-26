#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];

  size_t RowsNumber() const {
    return N;
  }

  size_t ColumnsNumber() const {
    return M;
  }

  T& operator()(size_t i, size_t j) {
    return matrix[i][j];
  }

  T operator()(size_t i, size_t j) const {
    return matrix[i][j];
  }

  T& At(size_t i, size_t j) {
    if (i < 0 || i > N - 1 || j < 0 || j > M - 1) {
      throw MatrixOutOfRange{};
    }
    return matrix[i][j];
  }

  T At(size_t i, size_t j) const {
    if (i < 0 || i > N - 1 || j < 0 || j > M - 1) {
      throw MatrixOutOfRange{};
    }
    return matrix[i][j];
  }

  void operator=(Matrix<T, N, M> b) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] = b(i, j);
      }
    }
  }

  Matrix<T, N, M>& operator+=(Matrix<T, N, M> a) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] += a(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator-=(Matrix<T, N, M> a) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] -= a(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(Matrix<T, M, M> a) {
    T mlt[N][M];
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        mlt[i][j] = 0;
        for (size_t s = 0; s < M; ++s) {
          mlt[i][j] += matrix[i][s] * a(s, j);
        }
      }
    }
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] = mlt[i][j];
      }
    }
    return *this;
  }

  template <class V>
  Matrix<T, N, M>& operator*=(V k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] *= k;
      }
    }
    return *this;
  }

  template <class V>
  Matrix<T, N, M>& operator/=(V k) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] /= k;
      }
    }
    return *this;
  }
};

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> a) {
  Matrix<T, M, N> b;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      b(j, i) = a(i, j);
    }
  }
  return b;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> a, Matrix<T, N, M> b) {
  Matrix<T, N, M> sum;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      sum(i, j) = a(i, j) + b(i, j);
    }
  }
  return sum;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> a, Matrix<T, N, M> b) {
  Matrix<T, N, M> dif;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      dif(i, j) = a(i, j) - b(i, j);
    }
  }
  return dif;
}

template <class T, size_t N, size_t M, size_t K>
Matrix<T, N, M> operator*(Matrix<T, N, K> a, Matrix<T, K, M> b) {
  Matrix<T, N, M> mlt;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mlt(i, j) = 0;
      for (size_t s = 0; s < K; ++s) {
        mlt(i, j) += a(i, s) * b(s, j);
      }
    }
  }
  return mlt;
}

template <class T, size_t N, size_t M, class V>
Matrix<T, N, M> operator*(Matrix<T, N, M> a, V k) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      a(i, j) *= k;
    }
  }
  return a;
}

template <class T, size_t N, size_t M, class V>
Matrix<T, N, M> operator*(V k, Matrix<T, N, M> a) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      a(i, j) *= k;
    }
  }
  return a;
}

template <class T, size_t N, size_t M, class V>
Matrix<T, N, M> operator/(Matrix<T, N, M> a, V k) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      a(i, j) /= k;
    }
  }
  return a;
}

template <class T, size_t N, size_t M>
bool operator==(Matrix<T, N, M> a, Matrix<T, N, M> b) {
  bool ans = true;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (a(i, j) != b(i, j)) {
        ans = false;
      }
    }
  }
  return ans;
}

template <class T, size_t N, size_t M>
bool operator!=(Matrix<T, N, M> a, Matrix<T, N, M> b) {
  bool ans = false;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (a(i, j) != b(i, j)) {
        ans = true;
      }
    }
  }
  return ans;
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& is, Matrix<T, N, M>& chel) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      is >> chel(i, j);
    }
  }
  return is;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& os, Matrix<T, N, M> chel) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M - 1; ++j) {
      os << chel(i, j) << " ";
    }
    os << chel(i, M - 1) << '\n';
  }
  return os;
}

template <class T>
void Swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <class T, size_t N>
void Transpose(Matrix<T, N, N>& chel) {
  for (size_t i = 0; i < N; ++i) {
    size_t j = 0;
    while (j < i) {
      Swap(chel(i, j), chel(j, i));
      ++j;
    }
  }
}

template <class T, size_t N>
T Trace(Matrix<T, N, N> chel) {
  T s = chel(0, 0);
  for (size_t i = 1; i < N; ++i) {
    s += chel(i, i);
  }
  return s;
}

template <class T, size_t N>
Matrix<T, N - 1, N - 1> Minor(Matrix<T, N, N> chel, size_t k, size_t l) {
  Matrix<T, N - 1, N - 1> chelik;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (i != k && j != l) {
        size_t i_ch = (i < k ? i : i - 1);
        size_t j_ch = (j < l ? j : j - 1);
        chelik(i_ch, j_ch) = chel(i, j);
      }
    }
  }
  return chelik;
}

template <class T>
T Determinant(Matrix<T, 1, 1> chel) {
  return chel(0, 0);
}

template <class T>
T Determinant(Matrix<T, 2, 2> chel) {
  return (chel(0, 0) * chel(1, 1) - chel(0, 1) * chel(1, 0));
}

template <class T, size_t N>
T Determinant(Matrix<T, N, N> chel) {
  T det = 0;
  for (size_t i = 0; i < N; ++i) {
    det += chel(0, i) * (i % 2 == 0 ? 1 : -1) * Determinant(Minor(chel, 0, i));
  }
  return det;
}

template <class T>
Matrix<T, 1, 1> GetInversed(Matrix<T, 1, 1> chel) {
  if (chel(0, 0) == 0) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<T, 1, 1> lehc{1 / chel(0, 0)};
  return lehc;
}

template <class T>
Matrix<T, 2, 2> GetInversed(Matrix<T, 2, 2> chel) {
  T det = Determinant(chel);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<T, 2, 2> lehc;
  T a = chel(0, 0);
  T b = chel(0, 1);
  T c = chel(1, 0);
  T d = chel(1, 1);
  lehc(0, 0) = d / det;
  lehc(0, 1) = -b / det;
  lehc(1, 0) = -c / det;
  lehc(1, 1) = a / det;
  return lehc;
}

template <class T, size_t N>
Matrix<T, N, N> GetInversed(Matrix<T, N, N> chel) {
  Matrix<T, N, N> lehc;
  T det = Determinant(chel);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      lehc(i, j) = ((i + j) % 2 == 0 ? 1 : -1) * Determinant(Minor(chel, j, i)) / det;
    }
  }
  return lehc;
}

template <class T>
void Inverse(Matrix<T, 1, 1>& chel) {
  if (chel(0, 0) == 0) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<T, 1, 1> lehc{1 / chel(0, 0)};
  chel = lehc;
}

template <class T>
void Inverse(Matrix<T, 2, 2>& chel) {
  T det = Determinant(chel);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  Matrix<T, 2, 2> lehc;
  T a = chel(0, 0);
  T b = chel(0, 1);
  T c = chel(1, 0);
  T d = chel(1, 1);
  lehc(0, 0) = d / det;
  lehc(0, 1) = -b / det;
  lehc(1, 0) = -c / det;
  lehc(1, 1) = a / det;
  chel = lehc;
}

template <class T, size_t N>
void Inverse(Matrix<T, N, N>& chel) {
  Matrix<T, N, N> lehc;
  T det = Determinant(chel);
  if (det == 0) {
    throw MatrixIsDegenerateError{};
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      lehc(i, j) = ((i + j) % 2 == 0 ? 1 : -1) * Determinant(Minor(chel, j, i)) / det;
    }
  }
  chel = lehc;
}
