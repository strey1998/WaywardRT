// WaywardRT/Samples/src/BlueWhite.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "spdlog/spdlog.h"

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Vec3.h"

static WaywardRT::Color ray_color(const WaywardRT::Ray& r) {
  WaywardRT::Vec3 unit_direction = r.direction().e();
  double t = 0.5 * (unit_direction.y + 1.0);
  WaywardRT::Color c1(1.0, 1.0, 1.0);
  WaywardRT::Color c2(0.5, 0.7, 1.0);
  WaywardRT::Color c = c1.lerp(c2, t);
  return c;
}

int main(int, const char**) {
  // IMAGE
  constexpr int IMAGE_WIDTH =   256;
  constexpr int IMAGE_HEIGHT =  256;
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
