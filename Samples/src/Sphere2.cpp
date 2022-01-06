// WaywardRT/Samples/src/Sphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <cmath>
#include <optional>

#include "spdlog/spdlog.h"

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Timer.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

static WaywardRT::Color ray_color(
    const WaywardRT::Ray& r,
    const WaywardRT::Hittable& world) {
  std::optional<WaywardRT::HitRecord> rec
    = world.hit(r, 0, WaywardRT::infinity);
  if (rec)
    return WaywardRT::Color(
      0.5 + 0.5*rec->n.x,
      0.5 + 0.5*rec->n.y,
      0.5 + 0.5*rec->n.z);

  WaywardRT::Vec3 unit_direction = r.direction().e();
  double t = 0.5 * (unit_direction.y + 1.0);
  WaywardRT::Color c1(1.0, 1.0, 1.0);
  WaywardRT::Color c2(0.5, 0.7, 1.0);
  return c1.lerp(c2, t);
}

int main(int, const char**) {
  // IMAGE
  constexpr int IMAGE_WIDTH =   2560;
  constexpr int IMAGE_HEIGHT =  1080;
  constexpr int SAMPLES = 100;
  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT, true);

  // WORLD
  WaywardRT::HittableList world;
  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(0, 0, -1), 0.5));
  world.add(std::make_shared<WaywardRT::Sphere>(
    WaywardRT::Vec3(0, -1000.5, -1), 1000));

  // CAMERA
  constexpr double VIEW_HEIGHT = 2.0;
  constexpr double VIEW_WIDTH = VIEW_HEIGHT * IMAGE_WIDTH / IMAGE_HEIGHT;
  constexpr double FOCAL_LENGTH = 1.0;
  WaywardRT::Camera cam(VIEW_HEIGHT, VIEW_WIDTH, FOCAL_LENGTH);

  // RENDER
  spdlog::info("Starting render");
  WaywardRT::Timer timer;
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
      WaywardRT::Color c(0, 0, 0);
      for (int s = 0; s < SAMPLES; ++s) {
        double u = (i + WaywardRT::random_double()) / (IMAGE_WIDTH - 1);
        double v = (j + WaywardRT::random_double()) / (IMAGE_HEIGHT - 1);
        WaywardRT::Ray r = cam.get_ray(u, v);
        c += ray_color(r, world) / SAMPLES;
      }
      image.setPixel(i, j, c);
    }
  }
  spdlog::info("Render complete in {:.1f}s", timer.elapsed());

  if (!image.write("test.bmp")) {
    spdlog::error("An error occurred");
    return -1;
  }

  return 0;
}
