// WaywardRT/Tests/src/Vec3Test.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <gtest/gtest.h>

#include <random>

#include "WaywardRT/Vec3.h"

namespace WaywardRT {

static constexpr int TEST_SIZE = 500;

TEST(Vec3, Addition) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v1 : vecs) {
    EXPECT_EQ(zero + v1, v1);
    EXPECT_EQ(v1 + zero, v1);
    for (const auto& v2 : vecs) {
      EXPECT_DOUBLE_EQ((v1 + v2).x(), v1.x() + v2.x());
      EXPECT_DOUBLE_EQ((v1 + v2).y(), v1.y() + v2.y());
      EXPECT_DOUBLE_EQ((v1 + v2).z(), v1.z() + v2.z());
    }
  }
}

TEST(Vec3, Subtraction) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v1 : vecs) {
    EXPECT_EQ(zero - v1, -v1);
    EXPECT_EQ(v1 - zero, v1);
    for (const auto& v2 : vecs) {
      EXPECT_DOUBLE_EQ((v1 - v2).x(), v1.x() - v2.x());
      EXPECT_DOUBLE_EQ((v1 - v2).y(), v1.y() - v2.y());
      EXPECT_DOUBLE_EQ((v1 - v2).z(), v1.z() - v2.z());
    }
  }
}

TEST(Vec3, DotProduct) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v1 : vecs) {
    EXPECT_DOUBLE_EQ(zero * v1, 0);
    EXPECT_DOUBLE_EQ(v1 * zero, 0);
    for (const auto& v2 : vecs) {
      EXPECT_DOUBLE_EQ(v1 * v2, v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z());
    }
  }
}

TEST(Vec3, ScalarMultiplication) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::array<double, TEST_SIZE> nums;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (auto& a : nums) {
    a = distr(eng);
  }

  for (const auto& v : vecs) {
    for (const auto& a : nums) {
      EXPECT_EQ(a*v, Vec3(a*v.x(), a*v.y(), a*v.z()));
      EXPECT_EQ(v*a, Vec3(a*v.x(), a*v.y(), a*v.z()));
    }
  }
}

TEST(Vec3, ScalarDivision) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::array<double, TEST_SIZE> nums;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (auto& a : nums) {
    a = distr(eng);
  }

  for (const auto& v : vecs) {
    for (const auto& a : nums) {
      EXPECT_EQ(v/a, Vec3(v.x()/a, v.y()/a, v.z()/a));
    }
  }
}

TEST(Vec3, CrossProduct) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v1 : vecs) {
    EXPECT_EQ(cross(v1, v1), Vec3());
    for (const auto& v2 : vecs) {
      EXPECT_DOUBLE_EQ(cross(v1, v2).x(), v1.y()*v2.z() - v1.z()*v2.y());
      EXPECT_DOUBLE_EQ(cross(v1, v2).y(), v1.z()*v2.x() - v1.x()*v2.z());
      EXPECT_DOUBLE_EQ(cross(v1, v2).z(), v1.x()*v2.y() - v1.y()*v2.x());
    }
  }
}

TEST(Vec3, Len) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v : vecs) {
    EXPECT_DOUBLE_EQ(v.len_sq(), v*v);
    EXPECT_DOUBLE_EQ(v.len(), sqrt(v*v));
  }
}

TEST(Vec3, UnitVector) {
  Vec3 zero;
  std::array<Vec3, TEST_SIZE> vecs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& v : vecs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v : vecs) {
    EXPECT_EQ(v.e(), v/sqrt(v*v));
  }
}

}  // namespace WaywardRT
