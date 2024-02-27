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
  auto &operator +=(Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    addAssign((T *) a, (const U *) b, N * M);
    return a;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto &operator -=(Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    subAssign((T *) a, (const U *) b, N * M);
    return a;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto &operator *=(Matrix<N, M, T> &a, U &b) noexcept {
    mulAssign((T *) a, b, N * M);
    return a;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto &operator /=(Matrix<N, M, T> &a, U &b) noexcept {
    divAssign((T *) a, b, N * M);
    return a;
  }
  // add/sub/mul/div assignments end

  // add/sub/mul/div begin
  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto operator +(const Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    add((V *) c, (const T *) a, (const U *) b, N * M);
    return c;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto operator -(const Matrix<N, M, T> &a, const Matrix<N, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    sub((V *) c, (const T *) a, (const U *) b, N * M);
    return c;
  }

  template<size_t N, size_t M, FloatingPoint T>
  auto operator -(const Matrix<N, M, T> &a) noexcept {
    Matrix<N, M, T> b;
    neg((T *) b, (const T *) a, N * M);
    return b;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto operator *(const Matrix<N, M, T> &a, U b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    mul((V *) c, (const T *) a, b, N * M);
    return c;
  }

  template<FloatingPoint T, size_t N, size_t M, FloatingPoint U>
  auto operator *(T a, const Matrix<N, M, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    mul((V *) c, a, (const U *) b, N * M);
    return c;
  }

  template<size_t N, size_t M, FloatingPoint T, FloatingPoint U>
  auto operator /(const Matrix<N, M, T> &a, U b) noexcept {
    using V = HigherPrecision<T, U>;
    Matrix<N, M, V> c;
    div((V *) c, (const T *) a, b, N * M);
    return c;
  }
  // add/sub/mul/div end
}
