cmake_minimum_required(VERSION 3.10)

project(stb_image_write
  VERSION 1.16
  LANGUAGES C
)

set(stb_image_write_INCLUDE_DIRS
  include
)

set(stb_image_write_SOURCE_FILES
  src/stb_image_write.c
)

add_library(stb_image_write ${stb_image_write_SOURCE_FILES})
target_include_directories(stb_image_write PUBLIC ${stb_image_write_INCLUDE_DIRS})
