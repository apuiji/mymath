#pragma once

#include<array>
#include<utility>
#include"xyz.hh"

namespace zlt::mymath {
  template<size_t N, FloatingPoint T = double>
  struct Vector: std::array<T, N> {
    Vector() = default;
    Vector(std::array<T, N> &&array) noexcept: std::array<T, N>(std::move(array)) {}
    template<size_t M, FloatingPoint U>
    inline Vector<N, T> &operator =(const Vector<M, U> &a) noexcept;
    template<size_t M, FloatingPoint U>
    inline constexpr operator Vector<M, U>() const noexcept;
  };

  // add/sub begin
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  constexpr auto add(const Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    return Vector<N, HigherPrecision<T, U>>({ (a[I] + b[I])... });
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto operator +(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return add(a, b, std::make_index_sequence<N>());
  }

  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  constexpr auto sub(const Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    return Vector<N, HigherPrecision<T, U>>({ (a[I] - b[I])... });
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto operator -(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return sub(a, b, std::make_index_sequence<N>());
  }
  // add/sub end

  // negative begin
  template<size_t N, FloatingPoint T, size_t ...I>
  constexpr auto neg(const Vector<N, T> &a, std::index_sequence<I...>) noexcept {
    return Vector<N, T>({ -a[I]... });
  }

  template<size_t N, FloatingPoint T>
  static inline constexpr auto operator -(const Vector<N, T> &a) noexcept {
    return neg(a, std::make_index_sequence<N>());
  }
  // negative end

  // mul/div begin
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  constexpr auto mul(const Vector<N, T> &a, U b, std::index_sequence<I...>) noexcept {
    return Vector<N, HigherPrecision<T, U>>({ (a[I] * b)... });
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto operator *(const Vector<N, T> &a, U b) noexcept {
    return mul(a, b, std::make_index_sequence<N>());
  }

  template<FloatingPoint T, size_t N, FloatingPoint U>
  static inline constexpr auto operator *(T a, const Vector<N, U> &b) noexcept {
    return mul(b, a, std::make_index_sequence<N>());
  }

  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  constexpr auto div(const Vector<N, T> &a, U b, std::index_sequence<I...>) noexcept {
    return Vector<N, HigherPrecision<T, U>>({ (a[I] / b)... });
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto operator /(const Vector<N, T> &a, U b) noexcept {
    return div(a, b, std::make_index_sequence<N>());
  }
  // mul/div end

  // equals begin
  template<size_t N, FloatingPoint T, FloatingPoint U>
  requires (!std::is_same_v<T, U>)
  static inline constexpr bool operator ==(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    using V = HigherPrecision<T, U>;
    if constexpr (std::is_same_v<T, V>) {
      return a == (Vector<N, T>) b;
    } else {
      return (Vector<N, U>) a == b;
    }
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr bool operator !=(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return !(a == b);
  }
  // equals end

  // assign and cast begin
  template<size_t N, FloatingPoint T, size_t M, FloatingPoint U, size_t ...I>
  int assign(Vector<N, T> &dest, const Vector<M, U> &src, std::index_sequence<I...>) noexcept {
    ((dest[I] = (T) src[I]), ...);
    return 0;
  }

  template<size_t N, FloatingPoint T, size_t M, FloatingPoint U>
  static inline int assign(Vector<N, T> &dest, const Vector<M, U> &src) noexcept {
    return assign(dest, src, std::make_index_sequence<N < M ? N : M>());
  }

  template<size_t N, FloatingPoint T>
  template<size_t M, FloatingPoint U>
  inline Vector<N, T> &Vector<N, T>::operator =(const Vector<M, U> &a) noexcept {
    assign(*this, a);
    return *this;
  }

  template<size_t N, FloatingPoint T>
  template<size_t M, FloatingPoint U>
  inline constexpr Vector<N, T>::operator Vector<M, U>() const noexcept {
    Vector<M, U> a;
    assign(a, *this);
    return a;
  }
  // assign and cast end

  // complex assign begin
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  int addAssign(Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    ((a[I] += b[I]), ...);
    return 0;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline auto &operator +=(Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    addAssign(a, b, std::make_index_sequence<N>());
    return a;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  int subAssign(Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    ((a[I] -= b[I]), ...);
    return 0;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline auto &operator -=(Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    subAssign(a, b, std::make_index_sequence<N>());
    return a;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  int mulAssign(Vector<N, T> &a, U b, std::index_sequence<I...>) noexcept {
    ((a[I] *= b), ...);
    return 0;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline auto &operator *=(Vector<N, T> &a, U b) noexcept {
    mulAssign(a, b, std::make_index_sequence<N>());
    return a;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  int divAssign(Vector<N, T> &a, U b, std::index_sequence<I...>) noexcept {
    ((a[I] /= b), ...);
    return 0;
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline auto &operator /=(Vector<N, T> &a, U b) noexcept {
    divAssign(a, b, std::make_index_sequence<N>());
    return a;
  }
  // complex assign end

  // dot/norm begin
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  constexpr auto dot2(const Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    return ((a[I] * b[I]) + ...);
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto dot2(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return dot2(a, b, std::make_index_sequence<I...>());
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto dot(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return std::sqrt(dot2(a, b));
  }

  template<size_t N, FloatingPoint T, size_t ...I>
  constexpr auto norm2(const Vector<N, T> &a, std::index_sequence<I...>) noexcept {
    return ((a[I] * a[I]) + ...);
  }

  template<size_t N, FloatingPoint T>
  static inline constexpr auto norm2(const Vector<N, T> &a) noexcept {
    return norm2(a, std::make_index_sequence<N>());
  }

  template<size_t N, FloatingPoint T>
  static inline constexpr auto norm(const Vector<N, T> &a) noexcept {
    return std::sqrt(norm2(a));
  }
  // dot/norm end

  template<size_t N, FloatingPoint = double>
  using Point = Vector<N, FloatingPoint>;

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto distance2(const Point<N, T> &a, const Point<N, U> &b) noexcept {
    return norm2(b - a);
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto distance(const Point<N, T> &a, const Point<N, U> &b) noexcept {
    return std::sqrt(distance2(a, b));
  }
}
