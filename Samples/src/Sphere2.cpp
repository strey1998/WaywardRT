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

int main(int, const char**) {
  // IMAGE
  constexpr int IMAGE_WIDTH =   480;
  constexpr int IMAGE_HEIGHT =  270;
  constexpr int SAMPLES = 100;
  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT, true);

  // WORLD
  WaywardRT::HittableList world;

  std::shared_ptr<WaywardRT::Material> mGround
    = std::make_shared<WaywardRT::Lambertian>(WaywardRT::Color(0.8, 0.8, 0.0));
  std::shared_ptr<WaywardRT::Material> mCenter
    = std::make_shared<WaywardRT::Lambertian>(WaywardRT::Color(0.1, 0.2, 0.5));
  std::shared_ptr<WaywardRT::Material> mLeft
    = std::make_shared<WaywardRT::Dielectric>(1.5);
  std::shared_ptr<WaywardRT::Material> mRight
    = std::make_shared<WaywardRT::Metal>(WaywardRT::Color(0.8, 0.6, 0.2), 0.0);

  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(0.0, -100.5, -1.0), 100, mGround));
  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(0.0, 0.0, -1.0), 0.5, mCenter));
  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(-1.0, 0.0, -1.0), 0.5, mLeft));
  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(-1.0, 0.0, -1.0), -0.4, mLeft));
  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(1.0, 0.0, -1.0), 0.5, mRight));

  // CAMERA
  constexpr double VIEW_HEIGHT = 2.0;
  constexpr double VIEW_WIDTH = VIEW_HEIGHT * IMAGE_WIDTH / IMAGE_HEIGHT;
  constexpr double FOCAL_LENGTH = 1.0;
  WaywardRT::Camera cam(VIEW_HEIGHT, VIEW_WIDTH, FOCAL_LENGTH);

  // RENDER
  constexpr int DEPTH = 50;
  spdlog::info("Starting render");
  WaywardRT::Timer timer;
  int k = 0;
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
      WaywardRT::Color c(0, 0, 0);
      for (int s = 0; s < SAMPLES; ++s) {
        double u = (i + WaywardRT::random_double()) / (IMAGE_WIDTH - 1);
        double v = (j + WaywardRT::random_double()) / (IMAGE_HEIGHT - 1);
        WaywardRT::Ray r = cam.get_ray(u, v);
        c += ray_color(r, world, DEPTH) / SAMPLES;
      }
      image.setPixel(i, j, c.exp(0.5));
    }
    if ((i % static_cast<int>(IMAGE_WIDTH/20) == 0) && i > 0) {
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
