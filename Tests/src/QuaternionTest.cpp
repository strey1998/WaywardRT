// WaywardRT/Tests/src/QuaternionTest.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <gtest/gtest.h>

#include <random>

#include "WaywardRT/Quaternion.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

#ifdef WAYWARDRT_PRECISION_SINGLE
  #define EXPECT_REAL_EQ EXPECT_FLOAT_EQ
#else
  #define EXPECT_REAL_EQ EXPECT_DOUBLE_EQ
#endif

namespace WaywardRT {

static constexpr int TEST_SIZE = 500;

TEST(Quaternion, Addition) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (const auto& q1 : qs) {
    EXPECT_EQ(zero + q1, q1);
    EXPECT_EQ(q1 + zero, q1);
    for (const auto& q2 : qs) {
      EXPECT_REAL_EQ((q1 + q2).real_part(), q1.real_part() + q2.real_part());
      EXPECT_EQ((q1 + q2).vector_part(), q1.vector_part() + q2.vector_part());
    }
  }
}

TEST(Quaternion, Subtraction) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (const auto& q1 : qs) {
    EXPECT_EQ(zero + q1, q1);
    EXPECT_EQ(q1 + zero, q1);
    for (const auto& q2 : qs) {
      EXPECT_REAL_EQ((q1 - q2).real_part(), q1.real_part() - q2.real_part());
      EXPECT_EQ((q1 - q2).vector_part(), q1.vector_part() - q2.vector_part());
    }
  }
}

TEST(Quaternion, QuaternionMultiplication) {
  Quaternion zero;
  Quaternion one(1, 0, 0, 0);
  Quaternion a(1, 1, 1, 1);
  Quaternion b(2, -2, 3, 4);
  Quaternion c(0, 17, 23, -100);
  Quaternion d(10, 4, -6, -6);

  EXPECT_EQ(zero*zero, zero);
  EXPECT_EQ(zero*one, zero);
  EXPECT_EQ(one*zero, zero);
  EXPECT_EQ(one*one, one);

  EXPECT_EQ(a*zero, zero);
  EXPECT_EQ(a*one,  a);
  EXPECT_EQ(a*a,    Quaternion(-2, 2, 2, 2));
  EXPECT_EQ(a*b,    Quaternion(-3, 1, -1, 11));
  EXPECT_EQ(a*c,    Quaternion(60, -106, 140, -94));
  EXPECT_EQ(a*d,    Quaternion(18, 14, 14, -6));

  EXPECT_EQ(b*zero, zero);
  EXPECT_EQ(b*one,  b);
  EXPECT_EQ(b*a,    Quaternion(-3, -1, 11, 1));
  EXPECT_EQ(b*b,    Quaternion(-25, -8, 12, 16));
  EXPECT_EQ(b*c,    Quaternion(365, -358, -86, -297));
  EXPECT_EQ(b*d,    Quaternion(70, -6, 22, 28));

  EXPECT_EQ(c*zero, zero);
  EXPECT_EQ(c*one,  c);
  EXPECT_EQ(c*a,    Quaternion(60, 140, -94, -106));
  EXPECT_EQ(c*b,    Quaternion(365, 426, 178, -103));
  EXPECT_EQ(c*c,    Quaternion(-10818, 0, 0, 0));
  EXPECT_EQ(c*d,    Quaternion(-530, -568, -68, -1194));

  EXPECT_EQ(d*zero, zero);
  EXPECT_EQ(d*one,  d);
  EXPECT_EQ(d*a,    Quaternion(18, 14, -6, 14));
  EXPECT_EQ(d*b,    Quaternion(70, -18, 14, 28));
  EXPECT_EQ(d*c,    Quaternion(-530, 908, 528, -806));
  EXPECT_EQ(d*d,    Quaternion(12, 80, -120, -120));
}

TEST(Quaternion, VectorMultiplication) {
  Quaternion zero;
  std::array<Vec3, TEST_SIZE> vs;
  std::array<Quaternion, TEST_SIZE> qs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (auto& v : vs) {
    v = Vec3(distr(eng), distr(eng), distr(eng));
  }

  for (const auto& v : vs) {
    for (const auto& q : qs) {
      auto qv = Quaternion(0, v.x, v.y, v.z);
      EXPECT_EQ(q*v, q*qv);
      EXPECT_EQ(v*q, qv*q);
    }
  }
}

TEST(Quaternion, ScalarMultiplication) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;
  std::array<real, TEST_SIZE> reals;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (auto& r : reals) {
    r = distr(eng);
  }

  for (const auto& r : reals) {
    EXPECT_EQ(zero * r, Quaternion());
    EXPECT_EQ(r * zero, Quaternion());
    for (const auto& q : qs) {
      EXPECT_REAL_EQ((r*q).real_part(), r*q.real_part());
      EXPECT_EQ((r*q).vector_part(), r*q.vector_part());
      EXPECT_REAL_EQ((q*r).real_part(), r*q.real_part());
      EXPECT_EQ((q*r).vector_part(), r*q.vector_part());
    }
  }
}

TEST(Quaternion, ScalarDivision) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;
  std::array<double, TEST_SIZE> nums;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (auto& a : nums) {
    a = distr(eng);
  }

  for (const auto& q : qs) {
    for (const auto& a : nums) {
      EXPECT_EQ(q/a, Quaternion(q.real_part()/a, q.vector_part()/a));
    }
  }
}

TEST(Quaternion, Norm) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;

  EXPECT_REAL_EQ(zero.norm(), 0);
  EXPECT_REAL_EQ(Quaternion(4, 3, 2, 1).norm(), sqrt(30));
  EXPECT_REAL_EQ(Quaternion(1, 0, 0, 0).norm(), 1);
  EXPECT_REAL_EQ(Quaternion(1, 0, 0, 1).norm(), sqrt(2));
  EXPECT_REAL_EQ(Quaternion(1, -1, -1, 1).norm(), 2);
}

TEST(Quaternion, Conjugate) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (const auto& q : qs) {
    EXPECT_EQ(q.conjugate(), Quaternion(q.real_part(), -q.vector_part()));
  }
}

TEST(Quaternion, Normalize) {
  Quaternion zero;
  std::array<Quaternion, TEST_SIZE> qs;
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> distr(-10000.0, 10000.0);

  for (auto& q : qs) {
    q = Quaternion(distr(eng), distr(eng), distr(eng), distr(eng));
  }

  for (const auto& q : qs) {
    EXPECT_EQ(q.normalized(), q/q.norm());
  }
}

}  // namespace WaywardRT
