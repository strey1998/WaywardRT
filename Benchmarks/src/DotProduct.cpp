// WaywardRT/Benchmarks/DotProduct.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <benchmark/benchmark.h>

#include <vector>

#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

static void BM_dot_product(benchmark::State& s) {
  std::vector<WaywardRT::Vec3> vecs1;
  std::vector<WaywardRT::Vec3> vecs2;
  vecs1.reserve(65536);
  vecs2.reserve(65536);

  for (auto& v : vecs1) {
    v = WaywardRT::random_real()*WaywardRT::Vec3::random_unit();
  }

  for (auto& v : vecs2) {
    v = WaywardRT::random_real()*WaywardRT::Vec3::random_unit();
  }

  uint16_t i = 0;
  while (s.KeepRunning()) {
    auto s = vecs1[i] * vecs2[i];
  }
}
BENCHMARK(BM_dot_product);
