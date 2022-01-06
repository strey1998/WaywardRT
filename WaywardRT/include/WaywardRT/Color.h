// WaywardRT/WaywardRT/include/WaywardRT/Color.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_COLOR_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_COLOR_H_

#include <ostream>

#include "WaywardRT_export.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a color
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
struct WAYWARDRT_EXPORT Color {
  float r, g, b;

  Color(float r, float g, float b);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Linear interpolation
  /// @param other The other color
  /// @param t     The interpolation parameter
  /// @return A new color between the this and the other color, according to t.
  ///   Equal to this color for t=0.0, or to the other color if t=1.0.
  /// @throws std::out_of_range if t is not between 0.0 and 1.0
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Color lerp(const Color& other, double t) const;

  friend WAYWARDRT_EXPORT std::ostream& operator<<(
    std::ostream& os, const Color& v);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_COLOR_H_
