#pragma once

#include<utility>
#include"xyz.hh"

namespace zlt::mymath {
  template<size_t N, size_t M, FloatingPoint T = double>
  struct Matrix {
    using Row = std::array<T, M>;
    using Data = std::array<Row, N>;
    Data data;
    Matrix() = default;
    Matrix(const Data &data) noexcept: data(data) {}
    template<FloatingPoint U>
    Matrix(const Matrix<N, M, U> &src) noexcept {
      assign(data.front().data(), (const U *) src, N * M);
    }
    template<FloatingPoint U>
    auto &operator =(const Matrix<N, M, U> &src) noexcept {
      assign(operator T *(), (const U *) src, N * M);
      return *this;
    }
    operator T *() noexcept {
      return data.front().data();
    }
    operator const T *() const noexcept {
      return data.front().data();
    }
    Row &operator [](int i) noexcept {
      return data[i];
    }
    const Row &operator [](int i) const noexcept {
      return data[i];
    }
  };

  // add/sub/mul/div assignments begin
  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto &operator +=(Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    addAssign((T *) a, (const U *) b, N * M);
    return a;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto &operator -=(Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    subAssign((T *) a, (const U *) b, N * M);
    return a;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto &operator *=(Matrix<N, M, T> &a, U &b) noexcept {
    mulAssign((T *) a, b, N * M);
    return a;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto &operator /=(Matrix<N, M, T> &a, U &b) noexcept {
    divAssign((T *) a, b, N * M);
    return a;
  }
  // add/sub/mul/div assignments end

  // add/sub/mul/div begin
  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto operator +(const Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    add((V *) c, (const T *) a, (const U *) b, N * M);
    return c;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto operator -(const Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    sub((V *) c, (const T *) a, (const U *) b, N * M);
    return c;
  }

  template<size_t N, size_t M, FloatingPoint T>
  static inline auto operator -(const Matrix<N, M, T> &a) noexcept {
    Matrix<N, M, T> b;
    neg((T *) b, (const T *) a, N * M);
    return b;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto operator *(const Matrix<N, M, T> &a, U b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    mul((V *) c, (const T *) a, b, N * M);
    return c;
  }

  template<FloatingPoint T, size_t N, size_t M, FloatingPoint U>
  static inline auto operator *(T a, const Matrix<N, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    mul((V *) c, (const U *) b, a, N * M);
    return c;
  }

  /// 2 * 3       3 * 2    2 * 2
  /// [1, 2, 3] * [1, 2] = [1 * 1 + 2 * 3 + 3 * 5, 1 * 2 + 2 * 4 + 3 * 6]
  /// [4, 5, 6]   [3, 4]   [4 * 1 + 5 * 3 + 6 * 5, 4 * 2 + 5 * 2 + 6 * 6]
  ///             [5, 6]
  template<size_t N, size_t M, FloatingPoint T, size_t P, FloatingPoint U, FloatingPoint V, size_t ...I>
  int mul(
    Matrix<N, M, T> &dest, const Matrix<N, P, U> &a, const Matrix<P, M, V> &b, int i, int j, std::index_sequence<I...> seq
  ) noexcept {
    if (i < N) {
      if (j < M) {
        dest[i][j] = ((a[i][I] * b[I][j]) + ...);
        return mul(dest, a, b, i, j + 1, seq);
      } else {
        return mul(dest, a, b, i + 1, 0, seq);
      }
    } else {
      return 0;
    }
  }

  template<size_t N, size_t P, FloatingPoint T, size_t M, FloatingPoint U>
  static inline auto operator *(const Matrix<N, P, T> &a, const Matrix<P, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    mul(c, a, b, 0, 0, std::make_index_sequence<P>());
    return c;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  static inline auto operator /(const Matrix<N, M, T> &a, U b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    div((V *) c, (const T *) a, b, N * M);
    return c;
  }
  // add/sub/mul/div end

  template<size_t M, size_t N, FloatingPoint T, FloatingPoint U>
  int transposition(Matrix<M, N, T> &dest, const Matrix<N, M, U> &src, int i, int j) noexcept {
    if (i < N) {
      if (j < M) {
        dest[i][j] = src[j][i];
        return transposition(dest, src, i, j + 1);
      } else {
        return transposition(dest, src, i + 1, 0);
      }
    } else {
      return 0;
    }
  }
}
