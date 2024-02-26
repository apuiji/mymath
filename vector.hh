#pragma once

#include<array>
#include<utility>
#include"xyz.hh"

namespace zlt::mymath {
  template<size_t N, FloatingPoint T = double>
  struct Vector: std::array<T, N> {
    Vector() = default;
    Vector(std::array<T, N> &&array) noexcept: std::array<T, N>(std::move(array)) {}
    template<FloatingPoint U>
    inline Vector<N, T> &operator =(const Vector<N, U> &a) noexcept;
    template<FloatingPoint U>
    inline constexpr operator Vector<N, U>() const noexcept;
  };

  // add/sub begin
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  static constexpr auto add(const Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    return Vector<N, HigherPrecision<T, U>>({ (a[I] + b[I])... });
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto operator +(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return add(a, b, std::make_index_sequence<N>());
  }

  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  static constexpr auto sub(const Vector<N, T> &a, const Vector<N, U> &b, std::index_sequence<I...>) noexcept {
    return Vector<N, HigherPrecision<T, U>>({ (a[I] - b[I])... });
  }

  template<size_t N, FloatingPoint T, FloatingPoint U>
  static inline constexpr auto operator -(const Vector<N, T> &a, const Vector<N, U> &b) noexcept {
    return sub(a, b, std::make_index_sequence<N>());
  }
  // add/sub end

  // negative begin
  template<size_t N, FloatingPoint T, size_t ...I>
  static constexpr auto neg(const Vector<N, T> &a, std::index_sequence<I...>) noexcept {
    return Vector<N, T>({ -a[I]... });
  }

  template<size_t N, FloatingPoint T>
  static inline constexpr auto operator -(const Vector<N, T> &a) noexcept {
    return neg(a, std::make_index_sequence<N>());
  }
  // negative end

  // mul/div begin
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  static constexpr auto mul(const Vector<N, T> &a, U b, std::index_sequence<I...>) noexcept {
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
  static constexpr auto div(const Vector<N, T> &a, U b, std::index_sequence<I...>) noexcept {
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
  template<size_t N, FloatingPoint T, FloatingPoint U, size_t ...I>
  static int assign(Vector<N, T> &dest, const Vector<N, U> &src, std::index_sequence<I...>) noexcept {
    ((dest[I] = (T) src[I]), ...);
    return 0;
  }

  template<size_t N, FloatingPoint T>
  template<FloatingPoint U>
  inline Vector<N, T> &Vector<N, T>::operator =(const Vector<N, U> &a) noexcept {
    assign(*this, a, std::make_index_sequence<N>());
    return *this;
  }

  template<size_t N, FloatingPoint T>
  template<FloatingPoint U>
  inline constexpr Vector<N, T>::operator Vector<N, U>() const noexcept {
    Vector<N, U> a;
    assign(a, *this, std::make_index_sequence<N>());
    return a;
  }
  // assign and cast end

  // norm begin
  template<size_t N, FloatingPoint T, size_t ...I>
  static constexpr auto norm2(const Vector<N, T> &a, std::index_sequence<I...>) noexcept {
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
  // norm end
}
