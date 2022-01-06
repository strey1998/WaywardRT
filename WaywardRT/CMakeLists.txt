cmake_minimum_required(VERSION 3.10)

set(WaywardRT_INCLUDE_DIRS
  include
)
file(GLOB_RECURSE WaywardRT_HEADER_FILES include/*.h)

set(WaywardRT_SOURCE_FILES
  src/BMPImage.cpp
  src/Camera.cpp
  src/Color.cpp
  src/Ray.cpp
  src/Vec3.cpp
  src/Objects/Hittable.cpp
  src/Objects/HittableList.cpp
  src/Objects/Sphere.cpp
)

add_library(WaywardRT ${WaywardRT_SOURCE_FILES})
target_include_directories(WaywardRT PUBLIC ${WaywardRT_INCLUDE_DIRS})
target_include_directories(WaywardRT PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(WaywardRT PRIVATE spdlog::spdlog stb_image_write)

set_target_properties(WaywardRT PROPERTIES
  CXX_STANDARD               17
  CXX_STANDARD_REQUIRED      YES
  CXX_VISIBILITY_PRESET      hidden
  VISIBILITY_INLINES_HIDDEN  YES
)

if(WaywardRT_APPLY_CPPLINT AND NOT WaywardRT_CPPLINT_FILEPATH STREQUAL "")
  set_target_properties(WaywardRT
    PROPERTIES
      CXX_CPPLINT "${WaywardRT_CPPLINT_FILEPATH};--filter=-build/include-what-you-use"
  )
  if(WaywardRT_APPLY_CPPLINT_HEADERS)
    add_custom_command(TARGET WaywardRT PRE_LINK
      COMMAND ${WaywardRT_CPPLINT_FILEPATH}
        --filter=-build/include_what_you_use
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

if(MSVC)
  target_compile_options(WaywardRT PRIVATE /W4 /WX)
else()
  target_compile_options(WaywardRT PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-result)
endif()

include(GenerateExportHeader)
generate_export_header(WaywardRT EXPORT_FILE_NAME WaywardRT_export.h)
