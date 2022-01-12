cmake_minimum_required(VERSION 3.10)

set(WaywardRT_INCLUDE_DIRS
  include
)
file(GLOB WaywardRT_HEADER_FILES_ROOT       include/WaywardRT/*.h)
file(GLOB WaywardRT_HEADER_FILES_MATERIALS  include/WaywardRT/Materials/*.h)
file(GLOB WaywardRT_HEADER_FILES_OBJECTS    include/WaywardRT/Objects/*.h)
file(GLOB WaywardRT_HEADER_FILES_RENDERERS  include/WaywardRT/Renderers/*.h)
file(GLOB WaywardRT_HEADER_FILES_TEXTURES   include/WaywardRT/Textures/*.h)
set(WaywardRT_HEADER_FILES
  ${WaywardRT_HEADER_FILES_ROOT}
  ${WaywardRT_HEADER_FILES_MATERIALS}
  ${WaywardRT_HEADER_FILES_OBJECTS}
  ${WaywardRT_HEADER_FILES_RENDERERS}
  ${WaywardRT_HEADER_FILES_TEXTURES}
)

option(WaywardRT_ENABLE_LOGGING "Enable console logging in debug mode" YES)
option(WaywardRT_ENABLE_CONSOLE_LOGGING "Enable console logging in debug mode (this will disable progress bar)" NO)
option(WaywardRT_PRECISION_SINGLE "Use single precision floats" NO)

set(WaywardRT_SOURCE_FILES_ROOT
  src/BMPImage.cpp
  src/BoundingBox.cpp
  src/BVHNode.cpp
  src/Camera.cpp
  src/Color.cpp
  src/log.cpp
  src/Perlin.cpp
  src/Quaternion.cpp
  src/Ray.cpp
  src/Scene.cpp
  src/Vec3.cpp
 )
 set(WaywardRT_SOURCE_FILES_MATERIALS
  src/Materials/Dielectric.cpp
  src/Materials/DiffuseLight.cpp
  src/Materials/Isotropic.cpp
  src/Materials/Lambertian.cpp
  src/Materials/Material.cpp
  src/Materials/Metal.cpp
)
set(WaywardRT_SOURCE_FILES_OBJECTS
  src/Objects/Box.cpp
  src/Objects/ConstantMedium.cpp
  src/Objects/Hittable.cpp
  src/Objects/HittableList.cpp
  src/Objects/MovingSphere.cpp
  src/Objects/Rectangle.cpp
  src/Objects/Rotate.cpp
  src/Objects/Sphere.cpp
  src/Objects/Translate.cpp
 )
 set(WaywardRT_SOURCE_FILES_RENDERERS
  src/Renderers/Renderer.cpp
  src/Renderers/Renderer3D.cpp
  src/Renderers/RendererBasic.cpp
)
set(WaywardRT_SOURCE_FILES_TEXTURES
  src/Textures/Camo.cpp
  src/Textures/Checkered.cpp
  src/Textures/ImageTexture.cpp
  src/Textures/Marble.cpp
  src/Textures/SolidColor.cpp
  src/Textures/Texture.cpp
)
set(WaywardRT_SOURCE_FILES
  ${WaywardRT_SOURCE_FILES_ROOT}
  ${WaywardRT_SOURCE_FILES_MATERIALS}
  ${WaywardRT_SOURCE_FILES_OBJECTS}
  ${WaywardRT_SOURCE_FILES_RENDERERS}
  ${WaywardRT_SOURCE_FILES_TEXTURES}
)

source_group(include             FILES  ${WaywardRT_HEADER_FILES_ROOT})
source_group(include\\Materials  FILES  ${WaywardRT_HEADER_FILES_MATERIALS})
source_group(include\\Objects    FILES  ${WaywardRT_HEADER_FILES_OBJECTS})
source_group(include\\Renderers  FILES  ${WaywardRT_HEADER_FILES_RENDERERS})
source_group(include\\Textures   FILES  ${WaywardRT_HEADER_FILES_TEXTURES})

source_group(src             FILES  ${WaywardRT_SOURCE_FILES_ROOT})
source_group(src\\Materials  FILES  ${WaywardRT_SOURCE_FILES_MATERIALS})
source_group(src\\Objects    FILES  ${WaywardRT_SOURCE_FILES_OBJECTS})
source_group(src\\Renderers  FILES  ${WaywardRT_SOURCE_FILES_RENDERERS})
source_group(src\\Textures   FILES  ${WaywardRT_SOURCE_FILES_TEXTURES})

add_library(WaywardRT ${WaywardRT_SOURCE_FILES} ${WaywardRT_HEADER_FILES})
target_include_directories(WaywardRT PUBLIC ${WaywardRT_INCLUDE_DIRS})
target_include_directories(WaywardRT PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(WaywardRT PRIVATE stb_image stb_image_write progress_bar)

if(NOT MSVC)
target_link_libraries(WaywardRT PRIVATE pthread)
endif()

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
  target_compile_options(WaywardRT PRIVATE -Wall -Wextra -pedantic -Werror)
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
