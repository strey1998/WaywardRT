// WaywardRT/WaywardRT/include/WaywardRT/Perlin.h
// Copyright 2022 Trey Stoner
// All rights reserved

#ifndef WAYWARDRT_INCLUDE_WAYWARDRT_PERLIN_H_
#define WAYWARDRT_INCLUDE_WAYWARDRT_PERLIN_H_

#include <cstdint>

#include "WaywardRT_export.h"

#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

//////////////////////////////////////////////////////////////////////////////
/// Represents a BMP image
/// @author   Trey Stoner
/// @version  0.1.0
/// @since    0.1.0
//////////////////////////////////////////////////////////////////////////////
class WAYWARDRT_EXPORT Perlin {
 public:
  Perlin();
  ~Perlin();

  real noise(const Vec3& p) const;
  real turb(const Vec3& p, uint8_t depth = 7) const;
 private:
  static const int point_count = 256;
  Vec3* m_RanVec;
  int* m_PermX;
  int* m_PermY;
  int* m_PermZ;

  static int* generate_perm();
  static void permute(int* p, int n);
  static real perlin_interp(Vec3 c[2][2][2], real u, real v, real w);
};

}  // namespace WaywardRT

#endif  // WAYWARDRT_INCLUDE_WAYWARDRT_PERLIN_H_
