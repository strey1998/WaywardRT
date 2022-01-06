// WaywardRT/Samples/src/Sphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <cmath>
#include <optional>

#include "spdlog/spdlog.h"

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Ray.h"
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

  const WaywardRT::Vec3 ORIGIN = WaywardRT::Vec3(0.0, 0.0, 0.0);
  const WaywardRT::Vec3 HORIZONTAL = WaywardRT::Vec3(VIEW_WIDTH, 0.0, 0.0);
  const WaywardRT::Vec3 VERTICAL = WaywardRT::Vec3(0.0, VIEW_HEIGHT, 0.0);
  const WaywardRT::Vec3 CORNER = ORIGIN - HORIZONTAL/2 - VERTICAL/2
    - WaywardRT::Vec3(0.0, 0.0, FOCAL_LENGTH);

  // RENDER
  for (int i = 0; i < IMAGE_WIDTH; ++i) {
    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
      double u = static_cast<double>(i) / (IMAGE_WIDTH - 1);
      double v = static_cast<double>(j) / (IMAGE_HEIGHT - 1);
      WaywardRT::Ray r(ORIGIN, CORNER + u*HORIZONTAL + v*VERTICAL - ORIGIN);
      image.setPixel(i, j, ray_color(r, world));
    }
  }

  if (!image.write("test.bmp")) {
    spdlog::error("An error occurred");
    return -1;
  }

  spdlog::info("OK");
  return 0;
}
