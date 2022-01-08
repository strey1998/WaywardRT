// WaywardRT/Benchmarks/Render.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <benchmark/benchmark.h>

#include <random>
#include <vector>

#include "WaywardRT/Camera.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Materials/Dielectric.h"
#include "WaywardRT/Materials/Lambertian.h"
#include "WaywardRT/Materials/Metal.h"
#include "WaywardRT/Renderers/RendererBasic.h"
#include "WaywardRT/util.h"

static WaywardRT::HittableList spheres();

static void BM_ray_color(benchmark::State& s) {
  WaywardRT::HittableList world = spheres();
  WaywardRT::Camera camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, 1.0, 0.1);

  // Attempted to choose a more difficult area of the image to render
  constexpr double U_MIN = 0.412;
  constexpr double U_MAX = 0.413;
  constexpr double V_MIN = 0.7635;
  constexpr double V_MAX = 0.7645;

  srand(1123581321);  // For more consistent results (hopefully)

  while (s.KeepRunning()) {
    WaywardRT::RendererBasic::ray_color(
      camera.get_ray(
        WaywardRT::random_real(U_MIN, U_MAX),
        WaywardRT::random_real(V_MIN, V_MAX)),
      world, s.range(0));
  }
}
BENCHMARK(BM_ray_color)
  ->Arg(1)->Arg(16)->Arg(64)
  ->MinTime(5)
  ->Unit(benchmark::kMicrosecond);

static WaywardRT::HittableList spheres() {
  WaywardRT::HittableList world;

  auto mGround = std::make_shared<WaywardRT::Lambertian>(
    WaywardRT::Color(0.5, 0.5, 0.5));
  world.add(
    std::make_shared<WaywardRT::Sphere>(
      WaywardRT::Vec3(0, -1000, 0), 1000, mGround));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      double choose_material = WaywardRT::random_real();
      WaywardRT::Vec3 center(
        a + 0.9*WaywardRT::random_real(),
        0.2,
        b + 0.9*WaywardRT::random_real());

      if ((center - WaywardRT::Vec3(4, 0.2, 0)).len() > 0.9) {
        std::shared_ptr<WaywardRT::Material> material;

        if (choose_material < 0.8) {
          auto albedo = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          material = std::make_shared<WaywardRT::Lambertian>(albedo);
        } else if (choose_material < 0.95) {
          auto albedo = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          auto fuzz = WaywardRT::random_real(0, 0.5);
          material = std::make_shared<WaywardRT::Metal>(albedo, fuzz);
        } else {
          material = std::make_shared<WaywardRT::Dielectric>(1.5);
        }
        world.add(std::make_shared<WaywardRT::Sphere>(center, 0.2, material));
      }
    }
  }

  auto m1 = std::make_shared<WaywardRT::Dielectric>(1.5);
  auto m2 = std::make_shared<WaywardRT::Lambertian>(
    WaywardRT::Color(0.4, 0.2, 0.1));
  auto m3 = std::make_shared<WaywardRT::Metal>(
    WaywardRT::Color(0.7, 0.6, 0.5), 0.0);

  world.add(
    std::make_shared<WaywardRT::Sphere>(WaywardRT::Vec3(0, 1, 0), 1.0, m1));
  world.add(
    std::make_shared<WaywardRT::Sphere>(WaywardRT::Vec3(-4, 1, 0), 1.0, m2));
  world.add(
    std::make_shared<WaywardRT::Sphere>(WaywardRT::Vec3(4, 1, 0), 1.0, m3));

  return world;
}
