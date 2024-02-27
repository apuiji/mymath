#pragma once

#include<utility>
#include"xyz.hh"

namespace zlt::mymath {
  // assigners begin
  template<FloatingPoint T, FloatingPoint U>
  int assign(T *dest, const U *src, size_t n) noexcept {
    if (n) {
      *dest = *src;
      return assign(dest + 1, src + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U>
  int addAssign(T *dest, const U *src, size_t n) noexcept {
    if (n) {
      *dest += *src;
      return addAssign(dest + 1, src + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U>
  int subAssign(T *dest, const U *src, size_t n) noexcept {
    if (n) {
      *dest -= *src;
      return subAssign(dest + 1, src + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T>
  int negAssign(T *data, size_t n) noexcept {
    if (n) {
      *data = -*data;
      return negAssign(data + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U>
  int mulAssign(T *dest, U u, size_t n) noexcept {
    if (n) {
      *dest *= u;
      return mulAssign(dest + 1, u, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U>
  int divAssign(T *dest, U u, size_t n) noexcept {
    if (n) {
      *dest /= u;
      return divAssign(dest + 1, u, n - 1);
    } else {
      return 0;
    }
  }
  // assigners end

  // add/sub/mul/div begin
  template<FloatingPoint T, FloatingPoint U, FloatingPoint U1>
  int add(T *dest, const U *a, const U1 *b, size_t n) noexcept {
    if (n) {
      *dest = *a + *b;
      return add(dest + 1, a + 1, b + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U, FloatingPoint U1>
  int sub(T *dest, const U *a, const U1 *b, size_t n) noexcept {
    if (n) {
      *dest = *a - *b;
      return sub(dest + 1, a + 1, b + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U>
  int neg(T *dest, const U *src, size_t n) noexcept {
    if (n) {
      *dest = -*src;
      return neg(dest + 1, src + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U, FloatingPoint U1>
  int mul(T *dest, const U *a, U1 b, size_t n) noexcept {
    if (n) {
      *dest = *a * b;
      return mul(dest + 1, a + 1, b, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U, FloatingPoint U1>
  int div(T *dest, const U *a, U1 b, size_t n) noexcept {
    if (n) {
      *dest = *a / b;
      return div(dest + 1, a + 1, b, n - 1);
    } else {
      return 0;
    }
  }
  // add/sub/mul/div end

  template<FloatingPoint T, FloatingPoint U>
  bool equals(const T *a, const U *b, size_t n) noexcept {
    if (n) {
      return *a == *b && equals(a + 1, b + 1, n - 1);
    } else {
      return true;
    }
  }

  template<FloatingPoint T, FloatingPoint U, FloatingPoint U1>
  int dot(T &dest, const U *a, const U1 *b, size_t n) noexcept {
    if (n) {
      dest += *a * *b;
      return dot(dest, a + 1, b + 1, n - 1);
    } else {
      return 0;
    }
  }

  template<FloatingPoint T, FloatingPoint U>
  int norm2(T &dest, const U *src, size_t n) noexcept {
    if (n) {
      dest += *src * *src;
      return norm2(dest, src + 1, n - 1);
    } else {
      return 0;
    }
  }
}
