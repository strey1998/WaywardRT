cmake_minimum_required(VERSION 3.10)

set(WaywardRT_INCLUDE_DIRS
  include
)
file(GLOB_RECURSE WaywardRT_HEADER_FILES include/*.h)

option(WaywardRT_PRECISION_SINGLE NO "Use single precision floats")

set(WaywardRT_SOURCE_FILES
  src/BMPImage.cpp
  src/Camera.cpp
  src/Color.cpp
  src/log.cpp
  src/Ray.cpp
  src/Renderer.cpp
  src/Vec3.cpp
  src/Materials/Dielectric.cpp
  src/Materials/Lambertian.cpp
  src/Materials/Metal.cpp
  src/Objects/Hittable.cpp
  src/Objects/HittableList.cpp
  src/Objects/MovingSphere.cpp
  src/Objects/Sphere.cpp
)

add_library(WaywardRT ${WaywardRT_SOURCE_FILES})
target_include_directories(WaywardRT PUBLIC ${WaywardRT_INCLUDE_DIRS})
target_include_directories(WaywardRT PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(WaywardRT PRIVATE pthread stb_image_write progress_bar)

if(WaywardRT_PRECISION_SINGLE)
  target_compile_definitions(WaywardRT PUBLIC WAYWARDRT_PRECISION_SINGLE)
endif()

if(TARGET spdlog::spdlog)
  target_link_libraries(WaywardRT PRIVATE $<$<CONFIG:Debug>:spdlog::spdlog>)
  target_compile_definitions(WaywardRT PUBLIC $<$<CONFIG:Debug>:WAYWARDRT_ENABLE_LOGGING>)
  if(WaywardRT_ENABLE_CONSOLE_LOGGING)
    target_compile_definitions(WaywardRT PUBLIC $<$<CONFIG:Debug>:WAYWARDRT_ENABLE_CONSOLE_LOGGING>)
  endif()
endif()

set_target_properties(WaywardRT PROPERTIES
  CXX_STANDARD               17
  CXX_VISIBILITY_PRESET      hidden
  VISIBILITY_INLINES_HIDDEN  YES
)

if(MSVC)
  target_compile_options(WaywardRT PRIVATE /W4 /WX)
else()
  target_compile_options(WaywardRT PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-result)
endif()

if(WaywardRT_APPLY_CPPLINT AND NOT WaywardRT_CPPLINT_FILEPATH STREQUAL "")
  set_target_properties(WaywardRT
    PROPERTIES
      CXX_CPPLINT "${WaywardRT_CPPLINT_FILEPATH};--filter=-build/include-what-you-use,-build/c++11,-runtime/references"
  )
  if(WaywardRT_APPLY_CPPLINT_HEADERS)
    add_custom_command(TARGET WaywardRT PRE_LINK
      COMMAND ${WaywardRT_CPPLINT_FILEPATH}
        --filter=-build/include_what_you_use,-build/c++11,-runtime/references
        --root=${PROJECT_SOURCE_DIR}
        ${WaywardRT_HEADER_FILES})
  endif()
endif()

if(WaywardRT_APPLY_IWYU AND NOT WaywardRT_IWYU_FILEPATH STREQUAL "")
  set_target_properties(WaywardRT
    PROPERTIES
      CXX_INCLUDE_WHAT_YOU_USE ${WaywardRT_IWYU_FILEPATH}
  )
  if(WaywardRT_APPLY_IWYU_HEADERS)
    foreach(HEADER_FILE IN LISTS ${WaywardRT_HEADER_FILES})
      add_custom_command(TARGET WaywardRT PRE_LINK
      COMMAND ${WaywardRT_IWYU_FILEPATH} ${HEADER_FILE})
    endforeach()
  endif()
endif()

include(GenerateExportHeader)
generate_export_header(WaywardRT EXPORT_FILE_NAME WaywardRT_export.h)
