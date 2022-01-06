// WaywardRT/WaywardRT/include/WaywardRT/util.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_

#include <cstdlib>
#include <limits>

namespace WaywardRT {

// CONSTANTS
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.14159265358979323846264338327950288;

// FUNCTIONS
inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  return min + (max-min)*random_double();
}

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_UTIL_H_
