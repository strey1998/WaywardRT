// WaywardRT/WaywardRT/src/scenes.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Scene.h"

#include <utility>


#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Dielectric.h"
#include "WaywardRT/Materials/DiffuseLight.h"
#include "WaywardRT/Materials/Lambertian.h"
#include "WaywardRT/Materials/Metal.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Textures/Camo.h"
#include "WaywardRT/Textures/Checkered.h"
#include "WaywardRT/Textures/ImageTexture.h"
#include "WaywardRT/Textures/Marble.h"

namespace WaywardRT {

Scene Scene::RANDOM_SPHERES(float aspect_ratio) {
  Scene scene;

  // WORLD
  WaywardRT::HittableList world;
  auto tGround = std::make_shared<WaywardRT::Checkered>(
    WaywardRT::Color(0.2, 0.3, 0.1),
    WaywardRT::Color(0.9, 0.9, 0.9));

  auto mGround = std::make_shared<WaywardRT::Lambertian>(tGround);
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

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, aspect_ratio, 0.1);

  // BACKGROUND
  scene.background = Color(0.70, 0.80, 1.00);

  return scene;
}

Scene Scene::LIT_SPHERES(float aspect_ratio) {
  Scene scene;

  // WORLD
  WaywardRT::HittableList world;
  auto tGround = std::make_shared<WaywardRT::Checkered>(
    WaywardRT::Color(0.2, 0.3, 0.1),
    WaywardRT::Color(0.9, 0.9, 0.9));

  auto mGround = std::make_shared<WaywardRT::Lambertian>(tGround);
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


        if (choose_material < 0.12) {
          auto albedo = (0.5 * WaywardRT::Color::WHITE())
                      + (0.5 * WaywardRT::Color::Random());
          material = std::make_shared<WaywardRT::DiffuseLight>(albedo);
        } else if (choose_material < 0.5) {
          auto c1 = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          auto c2 = WaywardRT::Color::Random() * WaywardRT::Color::Random();
          material = std::make_shared<WaywardRT::Lambertian>(
            std::make_shared<WaywardRT::Marble>(c1, c2));
        } else if (choose_material < 0.8) {
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

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, aspect_ratio, 0.1);

  // BACKGROUND
  scene.background = Color(0.001, 0.001, 0.005);

  return scene;
}

Scene Scene::TWO_SPHERES(float aspect_ratio) {
  Scene scene;

  // WORLD
  WaywardRT::HittableList world;

  auto t1 = std::make_shared<Checkered>(
    Color(0.2, 0.3, 0.1),
    Color(0.9, 0.9, 0.9));

  world.add(std::make_shared<Sphere>(
    Vec3(0, -10, 0), 10,
    std::make_shared<Lambertian>(t1)));
  world.add(std::make_shared<Sphere>(
    Vec3(0, 10, 0), 10,
    std::make_shared<Lambertian>(t1)));

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, aspect_ratio);

  // BACKGROUND
  scene.background = Color(0.70, 0.80, 1.00);

  return scene;
}

Scene Scene::TWO_PERLIN_SPHERES(float aspect_ratio) {
  Scene scene;

  // WORLD
  WaywardRT::HittableList world;

  auto t1 = std::make_shared<Marble>(
    0.05*WaywardRT::Color::BLUE() + 0.75*WaywardRT::Color::WHITE(),
    0.75*WaywardRT::Color::BLUE() + 0.05*WaywardRT::Color::WHITE(),
    4);

  world.add(std::make_shared<Sphere>(
    Vec3(0, -1000, 0), 1000,
    std::make_shared<Lambertian>(t1)));
  world.add(std::make_shared<Sphere>(
    Vec3(0, 2, 0), 2,
    std::make_shared<Lambertian>(t1)));

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, aspect_ratio);

  // BACKGROUND
  scene.background = Color(0.70, 0.80, 1.00);

  return scene;
}

Scene Scene::EARTH(float aspect_ratio) {
  Scene scene;

  // WORLD
  WaywardRT::HittableList world;

  auto t1 = std::make_shared<ImageTexture>("earth.jpg");

  world.add(std::make_shared<Sphere>(
    Vec3(0, 0, 0), 2,
    std::make_shared<Lambertian>(t1)));

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(13, 2, 3),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, aspect_ratio);

  // BACKGROUND
  scene.background = Color(0.70, 0.80, 1.00);

  return scene;
}

}  // namespace WaywardRT