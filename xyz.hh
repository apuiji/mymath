#pragma once

#include<cmath>
#include<numbers>
#include<type_traits>

namespace zlt::mymath {
  template<class T>
  concept FloatingPoint = std::is_floating_point_v<T>;

  template<FloatingPoint T, FloatingPoint U>
  struct HigherPrecision_;

  template<FloatingPoint T, FloatingPoint U>
  requires (sizeof(T) >= sizeof(U))
  struct HigherPrecision_<T, U> {
    using Type = T;
  };

  template<FloatingPoint T, FloatingPoint U>
  struct HigherPrecision_ {
    using Type = typename HigherPrecision_<U, T>::Type;
  };

  template<FloatingPoint T, FloatingPoint U>
  using HigherPrecision = typename HigherPrecision_<T, U>::Type;

  static consteval long double operator ""_degree(long double value) {
    return value * std::numbers::pi_v<long double> / 180;
  }

  static consteval long double operator ""_pi(long double value) {
    return value * std::numbers::pi_v<long double>;
  }
}
