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
  #define FLOATING_POINT_EQUALITY_PRECISION 6
#else
  using real = double;
  #define FLOATING_POINT_EQUALITY_PRECISION 14
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
  return min + (max-min)*random_real();
}

inline real clamp(real x, real min, real max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_
