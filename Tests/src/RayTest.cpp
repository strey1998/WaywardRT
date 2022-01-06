// WaywardRT/Tests/src/RayTest.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <gtest/gtest.h>

#include <random>

#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"

namespace WaywardRT {

static constexpr int TEST_SIZE = 500;

TEST(Ray, at) {
  std::vector<Ray> rays;
  std::array<double, TEST_SIZE> vars;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (int i = 0; i < TEST_SIZE; ++i) {
    rays.push_back(Ray(
          Vec3(distr(eng), distr(eng), distr(eng)),
          Vec3(distr(eng), distr(eng), distr(eng))));
  }

  for (auto& t : vars) {
    t = distr(eng);
  }

  for (const auto& r : rays) {
    for (const auto& t : vars) {
      EXPECT_EQ(r.at(t), r.origin() + t*r.direction());
    }
  }
}

}  // namespace WaywardRT
