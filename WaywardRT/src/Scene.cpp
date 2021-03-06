// WaywardRT/WaywardRT/src/scenes.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Scene.h"

#include <cstdint>
#include <memory>

#include "WaywardRT/BVHNode.h"
#include "WaywardRT/Camera.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Materials/Dielectric.h"
#include "WaywardRT/Materials/DiffuseLight.h"
#include "WaywardRT/Materials/Lambertian.h"
#include "WaywardRT/Materials/Metal.h"
#include "WaywardRT/Objects/Box.h"
#include "WaywardRT/Objects/ConstantMedium.h"
#include "WaywardRT/Objects/HittableList.h"
#include "WaywardRT/Objects/MovingSphere.h"
#include "WaywardRT/Objects/Rectangle.h"
#include "WaywardRT/Objects/Rotate.h"
#include "WaywardRT/Objects/Sphere.h"
#include "WaywardRT/Objects/Translate.h"
#include "WaywardRT/Textures/Checkered.h"
#include "WaywardRT/Textures/ImageTexture.h"
#include "WaywardRT/Textures/Marble.h"
#include "WaywardRT/util.h"
#include "WaywardRT/Vec3.h"
namespace WaywardRT { class Hittable; }
namespace WaywardRT { class Material; }

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
  // auto m2 = std::make_shared<WaywardRT::Lambertian>(
  //   WaywardRT::Color(0.4, 0.2, 0.1));
  auto m2 = std::make_shared<WaywardRT::Lambertian>(
    std::make_shared<ImageTexture>("earth.jpg"));
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

Scene Scene::MIRRORED_SPHERES(float aspect_ratio) {
  Scene scene;

  // WORLD
  WaywardRT::HittableList world;
  auto tGround = std::make_shared<Checkered>(
    Color(0.2, 0.3, 0.1),
    Color(0.9, 0.9, 0.9));

  auto mGround = std::make_shared<Lambertian>(tGround);
  world.add(
    std::make_shared<Sphere>(
      Vec3(0, -1000, 0), 1000, mGround));

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

  auto m1 = std::make_shared<Dielectric>(1.5);
  auto m2 = std::make_shared<Lambertian>(
    Color(0.4, 0.2, 0.1));
  auto m3 = std::make_shared<Metal>(
    Color(0.7, 0.6, 0.5), 0.0);

  world.add(
    std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, m1));
  world.add(
    std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, m2));
  world.add(
    std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, m3));

  world.add(std::make_shared<Rectangle>(
    Vec3(-12, -1000, -1000),
    Vec3(0, 2000, 0),
    Vec3(0, 0, 2000),
    std::make_shared<Metal>(0.08*Color::CYAN() + 0.6*Color::WHITE(), 0.0)));

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

Scene Scene::SIMPLE_LIGHT(float aspect_ratio) {
  Scene scene;

  HittableList world;

  auto t1 = std::make_shared<Marble>(4.0);
  world.add(std::make_shared<Sphere>(
    Vec3(0, -1000, 0), 1000, std::make_shared<Lambertian>(t1)));
  world.add(std::make_shared<Sphere>(
    Vec3(0, 2, 0), 2, std::make_shared<Lambertian>(t1)));

  auto m1 = std::make_shared<DiffuseLight>(Color(4, 4, 4));
  world.add(std::make_shared<RectangleXY>(3, 5, 1, 3, -2, m1));
  world.add(std::make_shared<Sphere>(Vec3(0, 7, 0), 2, m1));

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(26, 3, 6),
    WaywardRT::Vec3(0, 2, 0),
    WaywardRT::Vec3(0, 1, 0),
    20, aspect_ratio);

  // BACKGROUND
  scene.background = Color();

  return scene;
}

Scene Scene::CORNELL_BOX(float aspect_ratio) {
  Scene scene;

  HittableList world;

  auto tRed   = std::make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
  auto tWhite = std::make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
  auto tGreen = std::make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
  auto tLight = std::make_shared<DiffuseLight>(Color(15, 15, 15));

  world.add(std::make_shared<RectangleYZ>(555, 0, 555, 0, 555, tGreen));
  world.add(std::make_shared<RectangleYZ>(0, 0, 555, 0, 555, tRed));
  world.add(std::make_shared<RectangleXZ>(213, 343, 554, 227, 332, tLight));
  world.add(std::make_shared<RectangleXZ>(0, 555, 0, 0, 555, tWhite));
  world.add(std::make_shared<RectangleXZ>(0, 555, 555, 0, 555, tWhite));
  world.add(std::make_shared<RectangleXY>(0, 555, 0, 555, 555, tWhite));

  std::shared_ptr<Hittable> box1
    = std::make_shared<Box>(Vec3(), Vec3(165, 330, 165), tWhite);
  box1 = std::make_shared<Rotate>(box1, Vec3(0, 1, 0), 0.2618);
  box1 = std::make_shared<Translate>(box1, Vec3(265, 0, 295));
  world.add(box1);

  std::shared_ptr<Hittable> box2
    = std::make_shared<Box>(Vec3(), Vec3(165, 165, 165), tWhite);
  box2 = std::make_shared<Rotate>(box2, Vec3(0, 1, 0), -0.3142);
  box2 = std::make_shared<Translate>(box2, Vec3(130, 0, 65));
  world.add(box2);

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(278, 278, -800),
    WaywardRT::Vec3(278, 278, 0),
    WaywardRT::Vec3(0, 1, 0),
    40, aspect_ratio);

  // BACKGROUND
  scene.background = Color();

  return scene;
}

Scene Scene::CORNELL_BOX_MEDIA(float aspect_ratio) {
  Scene scene;

  HittableList world;

  auto tRed   = std::make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
  auto tWhite = std::make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
  auto tGreen = std::make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
  auto tLight = std::make_shared<DiffuseLight>(Color(7, 7, 7));

  world.add(std::make_shared<RectangleYZ>(555, 0, 555, 0, 555, tGreen));
  world.add(std::make_shared<RectangleYZ>(0, 0, 555, 0, 555, tRed));
  world.add(std::make_shared<RectangleXZ>(113, 443, 554, 127, 432, tLight));
  world.add(std::make_shared<RectangleXZ>(0, 555, 0, 0, 555, tWhite));
  world.add(std::make_shared<RectangleXZ>(0, 555, 555, 0, 555, tWhite));
  world.add(std::make_shared<RectangleXY>(0, 555, 0, 555, 555, tWhite));

  std::shared_ptr<Hittable> box1
    = std::make_shared<Box>(Vec3(), Vec3(165, 330, 165), tWhite);
  box1 = std::make_shared<Rotate>(box1, Vec3(0, 1, 0), 0.2618);
  box1 = std::make_shared<Translate>(box1, Vec3(265, 0, 295));
  world.add(std::make_shared<ConstantMedium>(box1, 0.01, Color(0, 0, 0)));

  std::shared_ptr<Hittable> box2
    = std::make_shared<Box>(Vec3(), Vec3(165, 165, 165), tWhite);
  box2 = std::make_shared<Rotate>(box2, Vec3(0, 1, 0), -0.3142);
  box2 = std::make_shared<Translate>(box2, Vec3(130, 0, 65));
  world.add(std::make_shared<ConstantMedium>(box2, 0.01, Color(1, 1, 1)));

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(278, 278, -800),
    WaywardRT::Vec3(278, 278, 0),
    WaywardRT::Vec3(0, 1, 0),
    40, aspect_ratio);

  // BACKGROUND
  scene.background = Color();

  return scene;
}

Scene Scene::ROTATION_TEST(float aspect_ratio) {
  Scene scene;

  HittableList world;

  const Vec3 axis = Vec3(1, 2, 3).e();
  const real theta = 1.5422;

  auto mRed   = std::make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
  auto mWhite = std::make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
  auto mGreen = std::make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
  auto mBlack = std::make_shared<Lambertian>(Color(0.05, 0.05, 0.05));
  auto mCyan  = std::make_shared<Lambertian>(Color(0.10, 0.80, 0.80));
  auto mBlue  = std::make_shared<Lambertian>(Color(0.10, 0.10, 0.90));

  world.add(
    std::make_shared<Rotate>(
      std::make_shared<RectangleYZ>(-1, -1, 1, -1, 1, mRed),
      axis, theta));
  world.add(
    std::make_shared<Rotate>(
      std::make_shared<RectangleYZ>(1, -1, 1, -1, 1, mWhite),
      axis, theta));

  world.add(
    std::make_shared<Rotate>(
      std::make_shared<RectangleXZ>(-1, 1, -1, -1, 1, mGreen),
      axis, theta));
  world.add(
    std::make_shared<Rotate>(
      std::make_shared<RectangleXZ>(-1, 1, 1, -1, 1, mBlack),
      axis, theta));

  world.add(
    std::make_shared<Rotate>(
      std::make_shared<RectangleXY>(-1, 1, -1, 1, -1, mCyan),
      axis, theta));
  world.add(
    std::make_shared<Rotate>(
      std::make_shared<RectangleXY>(-1, 1, -1, 1, 1, mBlue),
      axis, theta));

  world.add(std::make_shared<Sphere>(Vec3(-5, 0, 0), 0.5, mRed));
  world.add(std::make_shared<Sphere>(Vec3(5, 0, 0), 0.5, mWhite));

  world.add(std::make_shared<Sphere>(Vec3(0, -5, 0), 0.5, mGreen));
  world.add(std::make_shared<Sphere>(Vec3(0, 5, 0), 0.5, mBlack));

  world.add(std::make_shared<Sphere>(Vec3(0, 0, -5), 0.5, mCyan));
  world.add(std::make_shared<Sphere>(Vec3(0, 0, 5), 0.5, mBlue));

  scene.world = world;

  // CAMERA
  scene.camera = Camera(
    WaywardRT::Vec3(10, 10, 10),
    WaywardRT::Vec3(0, 0, 0),
    WaywardRT::Vec3(0, 1, 0),
    40, aspect_ratio);

  // BACKGROUND
  scene.background = Color(1, 1, 1);

  return scene;
}

Scene Scene::FINAL_SCENE_2(float aspect_ratio) {
  Scene scene;

  HittableList world;

  HittableList boxes1;
  auto mGround = std::make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

  const uint8_t boxes_per_side = 20;
  for (int i = 0; i < boxes_per_side; ++i) {
    for (int j = 0; j < boxes_per_side; ++j) {
      auto w = 100.0;
      auto x0 = -1000.0 + i*w;
      auto z0 = -1000.0 + j*w;
      auto y0 = 0.0;
      auto x1 = x0 + w;
      auto y1 = random_real(1, 101);
      auto z1 = z0 + w;

      boxes1.add(std::make_shared<Box>(
        Vec3(x0, y0, z0),
        Vec3(x1, y1, z1),
        mGround));
    }
  }
  world.add(std::make_shared<BVHNode>(boxes1, 0, 1));

  auto mLight = std::make_shared<DiffuseLight>(Color(7, 7, 7));
  world.add(std::make_shared<RectangleXZ>(123, 423, 554, 147, 412, mLight));

  auto center1 = Vec3(400, 400, 200);
  auto vel = Vec3(30, 0, 0);
  auto mMovingSphere = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
  world.add(std::make_shared<MovingSphere>(
    center1, vel, 50, mMovingSphere));

  world.add(std::make_shared<Sphere>(
    Vec3(260, 150, 45), 50,
    std::make_shared<Dielectric>(1.5)));
  world.add(std::make_shared<Sphere>(
    Vec3(0, 150, 145), 50,
    std::make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)));

  auto boundary = std::make_shared<Sphere>(
    Vec3(360, 150, 145), 70,
    std::make_shared<Dielectric>(1.5));
  world.add(boundary);
  world.add(std::make_shared<ConstantMedium>(
    boundary, 0.2, Color(0.2, 0.4, 0.9)));
  boundary = std::make_shared<Sphere>(
    Vec3(0, 0, 0), 5000, std::make_shared<Dielectric>(1.5));
  world.add(std::make_shared<ConstantMedium>(boundary, 0.0001, Color(1, 1, 1)));

  auto mEarth = std::make_shared<Lambertian>(
    std::make_shared<ImageTexture>("earth.jpg"));
  world.add(std::make_shared<Sphere>(Vec3(400, 200, 400), 100, mEarth));

  auto mMarble = std::make_shared<Lambertian>(std::make_shared<Marble>(0.1));
  world.add(std::make_shared<Sphere>(Vec3(220, 280, 300), 80, mMarble));

  HittableList boxes2;
  auto mWhite = std::make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
  uint16_t ns = 1000;
  for (int j = 0; j < ns; ++j) {
    boxes2.add(std::make_shared<Sphere>(
      Vec3(
        random_real(0, 165),
        random_real(0, 165),
        random_real(0, 165)),
      10, mWhite));
  }
  world.add(std::make_shared<Translate>(
    std::make_shared<Rotate>(
      std::make_shared<BVHNode>(boxes2, 0.0, 1.0),
      Vec3(0, 1, 0),
      15*pi/180),
    Vec3(-100, 270, 395)));

  scene.world = world;

  scene.camera = Camera(
    Vec3(478, 278, -600),
    Vec3(278, 278, 0),
    WaywardRT::Vec3(0, 1, 0),
    40, aspect_ratio);
  scene.camera.set_ray_timing(0.0, 1.0);

  scene.background = Color();

  return scene;
}

}  // namespace WaywardRT
