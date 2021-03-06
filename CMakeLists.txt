cmake_minimum_required(VERSION 3.10)

include(WaywardRT-info.in)
project(${WaywardRT_PROJECT_NAME}
  VERSION ${WaywardRT_VERSION}
  DESCRIPTION ${WaywardRT_DESCRIPTION}
  LANGUAGES ${WaywardRT_LANGUAGES}
)

option(WaywardRT_BUILD_TESTS "Build the WaywardRT tests" NO)
option(WaywardRT_BUILD_BENCHMARKS "Build the WaywardRT benchmarks" NO)
option(WaywardRT_BUILD_SAMPLES "Build the WaywardRT samples" YES)

set(WaywardRT_CPPLINT_FILEPATH cpplint CACHE FILEPATH "Cpplinter executable")
set(WaywardRT_APPLY_CPPLINT NO CACHE BOOL "Run Cpplinter")
set(WaywardRT_APPLY_CPPLINT_HEADERS NO CACHE BOOL "Run Cpplinter on header files")

set(WaywardRT_IWYU_FILEPATH include-what-you-use CACHE FILEPATH "IWYU executable")
set(WaywardRT_APPLY_IWYU NO CACHE BOOL "Run IWYU")
set(WaywardRT_APPLY_IWYU_HEADERS NO CACHE BOOL "Run IWYU on header files")

# spdlog ----------------------------------------------------------------------
if(WaywardRT_ENABLE_LOGGING)
  add_subdirectory(spdlog)
  target_compile_options(spdlog PRIVATE -Wno-attributes)
endif()
# -----------------------------------------------------------------------------

# stb -------------------------------------------------------------
add_subdirectory(stb)
# -----------------------------------------------------------------------------

# progress_bar ----------------------------------------------------------------
add_subdirectory(progress_bar)
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
