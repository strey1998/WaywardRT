// WaywardRT/Samples/src/Sphere.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <cmath>

#include "spdlog/spdlog.h"

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"

static double hit_sphere(
    const WaywardRT::Vec3& center,
    double radius,
    const WaywardRT::Ray& r) {
  WaywardRT::Vec3 oc = r.origin() - center;
  double a = r.direction().len_sq();
  double bh = oc*r.direction();
  double c = oc.len_sq() - radius*radius;
  double d = bh*bh - a*c;
  if (d < 0.0) return -1.0;

  return (-bh - sqrt(d))/a;
}

static WaywardRT::Color ray_color(const WaywardRT::Ray& r) {
  const WaywardRT::Vec3 CENTER = WaywardRT::Vec3(0, 0, -1);
  constexpr double RADIUS = 0.5;

  double t = hit_sphere(CENTER, RADIUS, r);
  if (t > 0.0) {
    WaywardRT::Vec3 n = (r.at(t) - CENTER).e();
    return WaywardRT::Color((n.x+1)/2.0, (n.y+1)/2.0, (n.z+1)/2.0);
  }
  WaywardRT::Vec3 unit_direction = r.direction().e();
  t = 0.5 * (unit_direction.y + 1.0);
  WaywardRT::Color c1(1.0, 1.0, 1.0);
  WaywardRT::Color c2(0.5, 0.7, 1.0);
  return c1.lerp(c2, t);
}

int main(int, const char**) {
  // IMAGE
  constexpr int IMAGE_WIDTH =   2560;
  constexpr int IMAGE_HEIGHT =  1080;
  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT, true);

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
      image.setPixel(i, j, ray_color(r));
    }
  }

  if (!image.write("test.bmp")) {
    spdlog::error("An error occurred");
    return -1;
  }

  spdlog::info("OK");
  return 0;
}
