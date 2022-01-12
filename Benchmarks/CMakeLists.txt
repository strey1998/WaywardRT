cmake_minimum_required(VERSION 3.10)

if(NOT TARGET benchmark)
  find_package(benchmark REQUIRED)
endif()

set(WaywardRT_BENCHMARK_SOURCE_FILES
  src/DotProduct.cpp
  src/Normalize.cpp
  src/Render.cpp
)

add_executable(WaywardRTAllBenchmarks ${WaywardRT_BENCHMARK_SOURCE_FILES})
target_link_libraries(WaywardRTAllBenchmarks PRIVATE WaywardRT benchmark::benchmark_main)

set_target_properties(WaywardRTAllBenchmarks PROPERTIES
  CXX_STANDARD               17
  CXX_VISIBILITY_PRESET      hidden
  VISIBILITY_INLINES_HIDDEN  YES
)

if(MSVC)
  target_compile_options(WaywardRTAllBenchmarks
    PRIVATE
      /W4
      /WX
  )
else()
  target_compile_options(WaywardRTAllBenchmarks
    PRIVATE
      -Wall
      -Wextra
      -pedantic
      -Werror
      -Wno-unused-result
      -Wno-unused-variable
      $<$<CXX_COMPILER_ID:GNU>:-Wno-unused-but-set-variable>
  )
endif()

foreach(BENCHMARK_FILE IN LISTS WaywardRT_BENCHMARK_SOURCE_FILES)
  get_filename_component(BENCHMARK_TARGET ${BENCHMARK_FILE} NAME_WE)
  add_executable(${BENCHMARK_TARGET} ${BENCHMARK_FILE})
  target_link_libraries(${BENCHMARK_TARGET} WaywardRT benchmark::benchmark_main)

  set_target_properties(${BENCHMARK_TARGET} PROPERTIES
    CXX_STANDARD               17
    CXX_VISIBILITY_PRESET      hidden
    VISIBILITY_INLINES_HIDDEN  YES
  )

  if(WaywardRT_APPLY_CPPLINT AND NOT WaywardRT_CPPLINT_FILEPATH STREQUAL "")
    set_target_properties(${BENCHMARK_TARGET} PROPERTIES
      CXX_CPPLINT "${WaywardRT_CPPLINT_FILEPATH};--filter=-build/include-what-you-use,-build/c++11,-runtime/references"
    )
  endif()

  if(MSVC)
    target_compile_options(${BENCHMARK_TARGET}
      PRIVATE
        /W4
        /WX
    )
  else()
    target_compile_options(${BENCHMARK_TARGET}
      PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
        -Wno-unused-result
        -Wno-unused-variable
        $<$<CXX_COMPILER_ID:GNU>:-Wno-unused-but-set-variable>
    )
  endif()

endforeach()
