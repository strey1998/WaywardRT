// WaywardRT/Samples/src/main.cpp
// Copyright 2022 Trey Stoner
// All rights reserved

#include "spdlog/spdlog.h"

#include "WaywardRT/BMPImage.h"

int main(int, const char**) {
  constexpr int IMAGE_WIDTH =   256;
  constexpr int IMAGE_HEIGHT =  256;

  WaywardRT::BMPImage image(IMAGE_WIDTH, IMAGE_HEIGHT);

  for (int i = 0; i < IMAGE_WIDTH; ++i) {
    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
      image.setPixel(i, j,
        static_cast<uint8_t>(
          255.999 * static_cast<double>(i) / (IMAGE_WIDTH-1)),
        static_cast<uint8_t>(
          255.999 * static_cast<double>(IMAGE_HEIGHT-1-j) / (IMAGE_HEIGHT-1)),
        static_cast<uint8_t>(
          255.999 * 0.25));
    }
  }

  if (!image.write("test.bmp")) {
    spdlog::error("An error occurred");
    return -1;
  }

  spdlog::info("OK");
  return 0;
}
