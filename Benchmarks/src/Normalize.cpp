// WaywardRT/Benchmarks/Normalize.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <benchmark/benchmark.h>

#include <vector>

#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

static void BM_normalize(benchmark::State& s) {
  std::vector<WaywardRT::Vec3> vecs;
  vecs.reserve(65536);

  for (auto& v : vecs) {
    v = WaywardRT::random_real()*WaywardRT::Vec3::random_unit();
  }

  uint16_t i = 0;
  WaywardRT::Vec3 e;
  while (s.KeepRunning()) {
    benchmark::DoNotOptimize(e = vecs[i++].e());
  }
}
BENCHMARK(BM_normalize);
