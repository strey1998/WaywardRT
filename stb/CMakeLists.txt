cmake_minimum_required(VERSION 3.10)

project(stb
  VERSION 0.0
  LANGUAGES C
)

set(stb_INCLUDE_DIRS
  include
)

add_library(stb_image src/stb_image.c)
target_include_directories(stb_image PUBLIC ${stb_INCLUDE_DIRS})

add_library(stb_image_write src/stb_image_write.c)
target_include_directories(stb_image_write PUBLIC ${stb_INCLUDE_DIRS})

if (MSVC)
  target_compile_options(stb_image PRIVATE /W0)
  target_compile_options(stb_image_write PRIVATE /W0)
endif()
