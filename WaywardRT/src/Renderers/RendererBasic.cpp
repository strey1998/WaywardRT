// WaywardRT/WaywardRT/src/Renderers/RendererBasic.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "WaywardRT/Renderers/RendererBasic.h"

#include <unistd.h>

#include <atomic>
#include <thread>
#include <vector>

#include "progress_bar/progress_bar.h"

#include "WaywardRT/BVHNode.h"
#include "WaywardRT/Color.h"
#include "WaywardRT/Image.h"
#include "WaywardRT/log.h"
#include "WaywardRT/Materials/Material.h"
#include "WaywardRT/util.h"

namespace WaywardRT {

RendererBasic::RendererBasic(
  uint16_t width,
  uint16_t height,
  uint16_t samples,
  uint16_t depth,
  Color background,
  HittableList world,
  Camera camera)
    : RendererBasic(width,
                    height,
                    samples,
                    depth,
                    background,
                    world,
                    camera,
                    0.0, 0.0) { }

RendererBasic::RendererBasic(
    uint16_t width,
    uint16_t height,
    uint16_t samples,
    uint16_t depth,
    Color background,
    HittableList world,
    Camera camera,
    real t0,
    real t1)
      : m_Width(width),
        m_Height(height),
        m_Samples(samples),
        m_Depth(depth),
        m_Background(background),
        m_World(world),
        m_Camera(camera) {
  WLOG_TRACE("Initializing RendererBasic");
  WLOG_TRACE("Image width={}",    width);
  WLOG_TRACE("Image height={}",   height);
  WLOG_TRACE("Image samples={}",  samples);
  WLOG_TRACE("Image depth={}",    depth);

  m_ImageData = reinterpret_cast<Color*>(
    malloc(sizeof(Color) * m_Width * m_Height));

  m_BVH = BVHNode(m_World, t0, t1);
}

RendererBasic::~RendererBasic() {
  free(m_ImageData);
}

void RendererBasic::render(uint8_t thread_count, bool use_BVH) const {
  std::vector<std::thread> threads;
  std::vector<uint16_t> partition;

  WLOG_TRACE("Starting full render on {} threads", thread_count);

  for (int i = 0; i < thread_count; ++i) {
    partition.push_back(
      static_cast<uint16_t>(i*m_Height/static_cast<float>(thread_count)));
  }
  partition.push_back(m_Height);

  #ifdef WAYWARDRT_ENABLE_CONSOLE_LOGGING
    for (int i = 0; i < thread_count; ++i) {
      if (partition[i] >= partition[i+1]) continue;
      threads.push_back(std::thread([=] {
        render_subimage(0, m_Width, partition[i], partition[i+1]-1, use_BVH);
      }));
    }
  #else
    std::atomic<uint32_t> progress(0);

    for (int i = 0; i < thread_count; ++i) {
      if (partition[i] >= partition[i+1]) continue;
      threads.push_back(std::thread([=, &progress] {
        render_subimage(
          0, m_Width, partition[i], partition[i+1]-1, progress, use_BVH);
      }));
    }

    ProgressBar progressBar(thread_count*1000, "RENDER");
    progressBar.SetFrequencyUpdate(10000);
    progressBar.SetStyle("\u2588", " ");

    uint16_t progress_ = 0;
    while (progress_ < 1000*thread_count) {
      progress_ = progress.load();
      std::cout << progress_/thread_count << "%    \r";
      progressBar.Progressed(progress_);
      usleep(100000);
    }

    std::cout << std::endl;
  #endif

  for (auto& th : threads) {
    th.join();
  }

  WLOG_TRACE("Completed render");
}

void RendererBasic::render_subimage(
    uint16_t xMin, uint16_t xMax,
    uint16_t yMin, uint16_t yMax,
    bool use_BVH) const {
  if (xMax > m_Width - 1) xMax = m_Width - 1;
  if (yMax > m_Height - 1) yMax = m_Height - 1;

  WLOG_TRACE(
    "Starting render of region ({}, {})x({}, {})", xMin, xMax, yMin, yMax);

  if (use_BVH) {
    for (int j = yMin; j <= yMax; ++j) {
      for (int i = xMin; i <= xMax; ++i) {
        WaywardRT::Color c(0, 0, 0);
        for (int s = 0; s < m_Samples; ++s) {
          real u = (i + WaywardRT::random_real()) / (m_Width - 1);
          real v = (j + WaywardRT::random_real()) / (m_Height - 1);
          WaywardRT::Ray r = m_Camera.get_ray(u, v);
          c += ray_color(r, m_Background, m_BVH, m_Depth) / m_Samples;
        }
        m_ImageData[i+m_Width*j] = c;
      }
    }
  } else {
    for (int j = yMin; j <= yMax; ++j) {
      for (int i = xMin; i <= xMax; ++i) {
        WaywardRT::Color c(0, 0, 0);
        for (int s = 0; s < m_Samples; ++s) {
          real u = (i + WaywardRT::random_real()) / (m_Width - 1);
          real v = (j + WaywardRT::random_real()) / (m_Height - 1);
          WaywardRT::Ray r = m_Camera.get_ray(u, v);
          c += ray_color(r, m_Background, m_World, m_Depth) / m_Samples;
        }
        m_ImageData[i+m_Width*j] = c;
      }
    }
  }

  WLOG_TRACE(
    "Completed render of region ({}, {})x({}, {})", xMin, xMax, yMin, yMax);
}

void RendererBasic::render_subimage(
    uint16_t xMin, uint16_t xMax, uint16_t yMin, uint16_t yMax,
    std::atomic<uint32_t>& progress, bool use_BVH) const {
  if (xMax > m_Width - 1) xMax = m_Width - 1;
  if (yMax > m_Height - 1) yMax = m_Height - 1;

  WLOG_TRACE(
    "Starting render of region ({}, {})x({}, {})", xMin, xMax, yMin, yMax);

  int pixels_to_render = (xMax-xMin) * (yMax - yMin);
  if (pixels_to_render <= 0) {
    progress += 1000;
    return;
  }
  int pixels_per_update = pixels_to_render / 1000;

  int ij = 1;
  int progress_ = 0;

  if (use_BVH) {
    for (int j = yMin; j <= yMax; ++j) {
      for (int i = xMin; i <= xMax; ++i) {
        WaywardRT::Color c(0, 0, 0);
        for (int s = 0; s < m_Samples; ++s) {
          real u = (i + WaywardRT::random_real()) / (m_Width - 1);
          real v = (j + WaywardRT::random_real()) / (m_Height - 1);
          WaywardRT::Ray r = m_Camera.get_ray(u, v);
          c += ray_color(r, m_Background, m_BVH, m_Depth) / m_Samples;
        }
        m_ImageData[i+m_Width*j] = c;
        if (ij++ % pixels_per_update == 0 && progress_ < 1000) {
          progress_++;
          progress++;
        }
      }
    }
  } else {
    for (int j = yMin; j <= yMax; ++j) {
      for (int i = xMin; i <= xMax; ++i) {
        WaywardRT::Color c(0, 0, 0);
        for (int s = 0; s < m_Samples; ++s) {
          real u = (i + WaywardRT::random_real()) / (m_Width - 1);
          real v = (j + WaywardRT::random_real()) / (m_Height - 1);
          WaywardRT::Ray r = m_Camera.get_ray(u, v);
          c += ray_color(r, m_Background, m_World, m_Depth) / m_Samples;
        }
        m_ImageData[i+m_Width*j] = c;
        if (ij++ % pixels_per_update == 0 && progress_ < 1000) {
          progress_++;
          progress++;
        }
      }
    }
  }
  while (progress_ < 1000) {
    progress_++;
    progress++;
  }

  WLOG_TRACE(
    "Completed render of region ({}, {})x({}, {})", xMin, xMax, yMin, yMax);
}

const Color* RendererBasic::image_data() const noexcept { return m_ImageData; }

void RendererBasic::write_image_data(Image& image, real gamma) const {
  for (int j = 0; j < m_Height; ++j) {
    for (int i = 0; i < m_Width; ++i) {
      image.setPixel(i, j, m_ImageData[i+m_Width*j].exp(1/gamma));
    }
  }
}

Color RendererBasic::ray_color(
    const Ray& r,
    const Color& background,
    const Hittable& world,
    int depth) {
  if (depth <= 0) return WaywardRT::Color(0, 0, 0);

  HitRecord rec;
  if (!world.hit(r, 0.00001, WaywardRT::infinity, rec))
    return background;

  Color attenuation;
  Ray scattered;
  Color emitted = rec.material->emit(rec.u, rec.v, rec.point);
  if (!rec.material->scatter(r, rec, scattered, attenuation))
    return emitted;

  return emitted +
            attenuation * ray_color(scattered, background, world, depth-1);
}

}  // namespace WaywardRT
