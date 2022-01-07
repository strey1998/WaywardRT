cmake_minimum_required(VERSION 3.10)

include(WaywardRT-info.in)
project(${WaywardRT_PROJECT_NAME}
  VERSION ${WaywardRT_VERSION}
  DESCRIPTION ${WaywardRT_DESCRIPTION}
  LANGUAGES ${WaywardRT_LANGUAGES}
)

option(WaywardRT_BUILD_TESTS "Build the WaywardRT tests" YES)
option(WaywardRT_BUILD_SAMPLES "Build the WaywardRT samples" YES)
option(WaywardRT_BUILD_BENCHMARKS "Build the WaywardRT benchmarks" YES)

set(WaywardRT_CPPLINT_FILEPATH cpplint CACHE FILEPATH "Cpplinter executable")
set(WaywardRT_APPLY_CPPLINT YES CACHE BOOL "Run Cpplinter on source files (specify with CPPLINT_FILEPATH)")
set(WaywardRT_APPLY_CPPLINT_HEADERS NO CACHE BOOL "Run Cpplinter on header files (specify with CPPLINT_FILEPATH)")

set(WaywardRT_IWYU_FILEPATH include-what-you-use CACHE FILEPATH "IWYU executable")
set(WaywardRT_APPLY_IWYU YES CACHE BOOL "Run IWYU on source files (specify with CPPLINT_FILEPATH)")
set(WaywardRT_APPLY_IWYU_HEADERS YES CACHE BOOL "Run IWYU on header files (specify with CPPLINT_FILEPATH)")

# spdlog ----------------------------------------------------------------------
if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()
# -----------------------------------------------------------------------------

# stb_image_write -------------------------------------------------------------
add_subdirectory(stb_image_write)
# -----------------------------------------------------------------------------

# WaywardRT -------------------------------------------------------------------
add_subdirectory(WaywardRT)
# -----------------------------------------------------------------------------

# Tests -----------------------------------------------------------------------
if(WaywardRT_BUILD_TESTS)
  add_subdirectory(Tests)
endif()
# -----------------------------------------------------------------------------

# Samples ---------------------------------------------------------------------
if(WaywardRT_BUILD_SAMPLES)
  add_subdirectory(Samples)
endif()
# -----------------------------------------------------------------------------

# Benchmarks ------------------------------------------------------------------
if(WaywardRT_BUILD_BENCHMARKS)
  add_subdirectory(Benchmarks)
endif()
# -----------------------------------------------------------------------------
