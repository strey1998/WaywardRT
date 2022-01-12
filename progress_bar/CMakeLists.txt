cmake_minimum_required(VERSION 3.10)

project(progress_bar
  VERSION 0.1
  LANGUAGES CXX
)

set(progress_bar_INCLUDE_DIRS
  include
)

set(progress_bar_SOURCE_FILES
  src/progress_bar.cpp
)

add_library(progress_bar ${progress_bar_SOURCE_FILES})
target_include_directories(progress_bar PUBLIC ${progress_bar_INCLUDE_DIRS})

if(MSVC)
  target_compile_options(progress_bar PRIVATE /W0)
endif()