// WaywardRT/Samples/src/MovingSpheres.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include <cmath>
#include <optional>

#include "WaywardRT/BMPImage.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/log.h"
#include "WaywardRT/Materials/Dielectric.h"
#include "WaywardRT/Materials/Lambertian.h"
#include "WaywardRT/Materials/Metal.h"
#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/Objects/Hittable.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Objects/MovingSphere.h"
#include "WaywardRT/Ray.h"
#include "WaywardRT/Renderer.h"
#include "WaywardRT/Timer.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"

WaywardRT::HittableList spheres() {
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
          world.add(std::make_shared<WaywardRT::MovingSphere>(
            center,
            WaywardRT::Vec3(0, WaywardRT::random_real(0, 0.5), 0),
            0.2,
            material));
        } else if (choose_material < 0.95) {
          auto albedo = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          auto fuzz = WaywardRT::random_real(0, 0.5);
          material = std::make_shared<WaywardRT::Metal>(albedo, fuzz);
          world.add(std::make_shared<WaywardRT::Sphere>(center, 0.2, material));
        } else {
          material = std::make_shared<WaywardRT::Dielectric>(1.5);
          world.add(std::make_shared<WaywardRT::Sphere>(center, 0.2, material));
        }
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

int main(int, const char**) {
  // SETTINGS
  constexpr int IMAGE_WIDTH = 960;
  constexpr int IMAGE_HEIGHT =  540;
  constexpr int SAMPLES = 25;
  constexpr int DEPTH = 50;

  // LOG
  WLOG_SET_LEVEL(WLOG_LEVEL_TRACE);

  // IMAGE
  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT, true);

  // WORLD
  auto world = spheres();

  // CAMERA
  WaywardRT::Camera camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, static_cast<float>(IMAGE_WIDTH) / IMAGE_HEIGHT, 0.1);
  camera.set_ray_timing(0.0, 0.5);

  // RENDER
  WaywardRT::Renderer renderer(
    IMAGE_WIDTH, IMAGE_HEIGHT,
    SAMPLES, DEPTH,
    world, camera);

  WLOG_INFO("Starting render");
  WaywardRT::Timer timer;
  renderer.render(12);
  WLOG_INFO("Render complete in {:.1f}s", timer.elapsed());

  renderer.write_image_data(image, 2.0);
  if (!image.write("out.bmp")) {
    WLOG_ERROR("An error occurred");
    return -1;
  }

  return 0;
}