// WaywardRT/WaywardRT/include/WaywardRT/util.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_

#include <cstdlib>
#include <limits>

namespace WaywardRT {

#ifdef WAYWARDRT_PRECISION_SINGLE
  using real = float;
  #define FLOATING_POINT_EQUALITY_PRECISION 5
#else
  using real = double;
  #define FLOATING_POINT_EQUALITY_PRECISION 10
#endif

// CONSTANTS
constexpr real infinity = std::numeric_limits<real>::infinity();
constexpr real pi = 3.14159265358979323846264338327950288;

// FUNCTIONS
inline real degrees_to_radians(real degrees) {
  return degrees * pi / 180.0;
}

inline real random_real() {
  return rand() / (RAND_MAX + 1.0);
}

inline real random_real(real min, real max) {
  if (min == max) return min;
  return min + (max-min)*random_real();
}

template <typename T>
inline T random_int(T min, T max) {
  return static_cast<T>(random_real(min, max+1));
}

inline real clamp(real x, real min, real max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_
