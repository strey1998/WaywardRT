// WaywardRT/Samples/src/Sphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <cmath>
#include <optional>

#include "spdlog/spdlog.h"

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Dielectric.h"
#include "WaywardRT/Materials/Lambertian.h"
#include "WaywardRT/Materials/Metal.h"
#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Timer.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

static WaywardRT::Color ray_color(
    const WaywardRT::Ray& r,
    const WaywardRT::Hittable& world,
    int depth = 1) {
  if (depth <= 0) return WaywardRT::Color(0, 0, 0);

  std::optional<WaywardRT::HitRecord> rec
    = world.hit(r, 0.00001, WaywardRT::infinity);
  if (rec) {
    WaywardRT::Color attenuation;
    std::optional<WaywardRT::Ray> scattered
      = rec->material->scatter(r, rec.value(), attenuation);
    if (scattered)
      return attenuation * ray_color(scattered.value(), world, depth - 1);
    return WaywardRT::Color(0, 0, 0);
  }

  WaywardRT::Vec3 unit_direction = r.direction().e();
  double t = 0.5 * (unit_direction.y + 1.0);
  WaywardRT::Color c1(1.0, 1.0, 1.0);
  WaywardRT::Color c2(0.5, 0.7, 1.0);
  return c1.lerp(c2, t);
}

WaywardRT::HittableList random_scene() {
  WaywardRT::HittableList world;

  auto mGround = std::make_shared<WaywardRT::Lambertian>(
    WaywardRT::Color(0.5, 0.5, 0.5));
  world.add(
    std::make_shared<WaywardRT::Sphere>(
      WaywardRT::Vec3(0, -1000, 0), 1000, mGround));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      double choose_material = WaywardRT::random_double();
      WaywardRT::Vec3 center(
        a + 0.9*WaywardRT::random_double(),
        0.2,
        b + 0.9*WaywardRT::random_double());

      if ((center - WaywardRT::Vec3(4, 0.2, 0)).len() > 0.9) {
        std::shared_ptr<WaywardRT::Material> material;

        if (choose_material < 0.8) {
          auto albedo = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          material = std::make_shared<WaywardRT::Lambertian>(albedo);
        } else if (choose_material < 0.95) {
          auto albedo = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          auto fuzz = WaywardRT::random_double(0, 0.5);
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

  world.add(std::make_shared<WaywardRT::Sphere>(WaywardRT::Vec3(0, 1, 0), 1.0, m1));
  world.add(std::make_shared<WaywardRT::Sphere>(WaywardRT::Vec3(-4, 1, 0), 1.0, m2));
  world.add(std::make_shared<WaywardRT::Sphere>(WaywardRT::Vec3(4, 1, 0), 1.0, m3));

  return world;
}

int main(int, const char**) {
  // IMAGE
  constexpr int IMAGE_WIDTH =   225;
  constexpr int IMAGE_HEIGHT =  150;
  constexpr int SAMPLES = 10;
  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT, true);

  // WORLD
  auto world = random_scene();

  // CAMERA
  WaywardRT::Camera cam(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, IMAGE_WIDTH / IMAGE_HEIGHT, 0.1);

  // RENDER
  constexpr int DEPTH = 50;
  spdlog::info("Starting render");
  WaywardRT::Timer timer;
  int k = 0;
  for (int j = 0; j < IMAGE_HEIGHT; ++j) {
    for (int i = 0; i < IMAGE_WIDTH; ++i) {
      WaywardRT::Color c(0, 0, 0);
      for (int s = 0; s < SAMPLES; ++s) {
        double u = (i + WaywardRT::random_double()) / (IMAGE_WIDTH - 1);
        double v = (j + WaywardRT::random_double()) / (IMAGE_HEIGHT - 1);
        WaywardRT::Ray r = cam.get_ray(u, v);
        c += ray_color(r, world, DEPTH) / SAMPLES;
      }
      image.setPixel(i, j, c.exp(0.5));
    }
    if ((j % static_cast<int>(IMAGE_HEIGHT/20) == 0) && j > 0) {
      spdlog::info("Render: {}%", 5*(++k));
    }
  }
  spdlog::info("Render complete in {:.1f}s", timer.elapsed());

  if (!image.write("test.bmp")) {
    spdlog::error("An error occurred");
    return -1;
  }

  return 0;
}
