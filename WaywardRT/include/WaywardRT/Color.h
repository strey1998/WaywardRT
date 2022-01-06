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
  static Color WHITE() { return Color(1, 1, 1); }
  static Color BLACK() { return Color(0, 0, 0); }
  static Color RED() { return Color(1, 0, 0); }
  static Color GREEN() { return Color(0, 1, 0); }
  static Color BLUE() { return Color(0, 0, 1); }
  static Color YELLOW() { return Color(1, 1, 0); }
  static Color MAGENTA() { return Color(1, 0, 1); }
  static Color CYAN() { return Color(0, 1, 1); }

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

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Color exponentiation, for gamma correction, etc.
  /// @param e The exponent
  /// @return A new color with each channel equal to this color's to the power
  ///   other
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Color exp(double e) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Color addition
  /// @param other The other color
  /// @return A new color equal to the sum of this color's channels with those
  ///   of the other, capped at 1.0
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Color operator+(const Color& other) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Color subtraction
  /// @param other The other color
  /// @return A new color equal to the difference of this color's channels with
  ///   those of the other, clipped to [0.0, 1.0]
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Color operator-(const Color& other) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Color multiplication
  /// @param other The factor by which to multiply
  /// @return A new color with each channel equal to this color times other,
  ///   clipped to [0.0, 1.0]
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Color operator*(double other) const;

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Color multiplication
  /// @param factor The factor by which to multiply
  /// @param color  The color to multiply
  /// @return A new color with each channel equal to color's times other
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] friend WAYWARDRT_EXPORT Color operator*(
    double factor, const Color& color);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Color division
  /// @param other The factor by which to divide
  /// @return A new color with each channel equal to this color divided by other
  //////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] Color operator/(double other) const;

  Color& operator+=(const Color& other);
  Color& operator-=(const Color& other);
  Color& operator*=(double other);
  Color& operator/=(double other);

  friend WAYWARDRT_EXPORT std::ostream& operator<<(
    std::ostream& os, const Color& v);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_COLOR_H_
