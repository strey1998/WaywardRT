// WaywardRT/WaywardRT/src/Perlin.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Perlin.h"

#include <cmath>

#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

Perlin::Perlin() {
  m_RanVec = new Vec3[point_count];
  for (int i = 0; i < point_count; ++i) {
    m_RanVec[i] = Vec3::random_unit();
  }

  m_PermX = generate_perm();
  m_PermY = generate_perm();
  m_PermZ = generate_perm();
}

Perlin::~Perlin() {
  delete[] m_RanVec;
  delete[] m_PermX;
  delete[] m_PermY;
  delete[] m_PermZ;
}

real Perlin::noise(const Vec3& p) const {
  real u = p.x - floor(p.x);
  real v = p.y - floor(p.y);
  real w = p.z - floor(p.z);

  int i = static_cast<int>(floor(p.x));
  int j = static_cast<int>(floor(p.y));
  int k = static_cast<int>(floor(p.z));

  Vec3 c[2][2][2];

  for (int di = 0; di < 2; ++di) {
    for (int dj = 0; dj < 2; ++dj) {
      for (int dk = 0; dk < 2; ++dk) {
        c[di][dj][dk] = m_RanVec[
          m_PermX[(i+di) & 0xFF] ^
          m_PermX[(j+dj) & 0xFF] ^
          m_PermX[(k+dk) & 0xFF]];
      }
    }
  }

  return perlin_interp(c, u, v, w);
}

real Perlin::turb(const Vec3& p, uint8_t depth) const {
  real accum = 0.0;
  Vec3 p2 = p;
  real weight = 1.0;

  for (int i = 0; i < depth; ++i) {
    accum += weight*noise(p2);
    weight *= 0.5;
    p2 *= 2;
  }

  return fabs(accum);
}

int* Perlin::generate_perm() {
  int* p = new int[point_count];

  for (int i = 0; i < point_count; ++i) {
    p[i] = i;
  }

  permute(p, point_count);

  return p;
}

void Perlin::permute(int* p, int n) {
  for (int i = n-1; i > 0; --i) {
    int target = random_int(0, i);
    int tmp = p[i];
    p[i] = p[target];
    p[target] = tmp;
  }
}

real Perlin::perlin_interp(Vec3 c[2][2][2], real u, real v, real w) {
  real uu = u*u*(3-2*u);
  real vv = v*v*(3-2*v);
  real ww = w*w*(3-2*w);
  real accum = 0.0;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        Vec3 weight_v(u-i, v-j, w-k);
        accum += (i*uu + (1-i)*(1-uu))
               * (j*vv + (1-j)*(1-vv))
               * (k*ww + (1-k)*(1-ww))
               * (c[i][j][k]*weight_v);
      }
    }
  }

  return accum;
}

}  // namespace WaywardRT
