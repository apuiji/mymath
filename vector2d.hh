#pragma once

#include"vector.hh"

namespace zlt::mymath {
  template<FloatingPoint T = double>
  using Vector2d = Vector<2, T>;

  template<FloatingPoint T>
  inline constexpr auto radians(const Vector2d<T> &a) noexcept {
    return std::atan(a[1] / a[0]);
  }

  template<FloatingPoint T, FloatingPoint U>
  inline constexpr auto polar(T arc, U norm = 1) noexcept {
    return Vector2d<HigherPrecision<T, U>>({ norm * std::cos(arc), norm * std::sin(arc) });
  }

  /// (a + bi)(c + di)
  /// ac + adi + bci - bd
  /// (ac - bd) + (ad + bc)i
  template<FloatingPoint T, FloatingPoint U>
  constexpr auto complex2dMul(const Vector2d<T> &x, const Vector2d<U> &y) noexcept {
    auto &a = x[0];
    auto &b = x[1];
    auto &c = y[0];
    auto &d = y[1];
    return Vector2d<HigherPrecision<T, U>>({ a * c - b * d, a * d + b * c });
  }

  /// (a + bi) / (c + di)
  /// (a + bi)(c - di) / (cc + dd)
  /// (ac - adi + bci + bd) / e; e = cc + dd
  /// (ac + bd) / e + (bc - ad)i / e
  template<FloatingPoint T, FloatingPoint U>
  constexpr auto complex2dDiv(const Vector2d<T> &x, const Vector2d<U> &y) noexcept {
    auto &a = x[0];
    auto &b = x[1];
    auto &c = y[0];
    auto &d = y[1];
    auto e = c * c + d * d;
    return Vector2d<HigherPrecision<T, U>>({ (a * c + b * d) / e, (b * c - a * d) / e });
  }

  template<FloatingPoint T, FloatingPoint U>
  static inline constexpr auto rotate(const Vector2d<T> &v, U arc) noexcept {
    return complex2dMul(v, makeFromPolar(arc));
  }
}
