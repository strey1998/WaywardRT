cmake_minimum_required(VERSION 3.10)

if(NOT TARGET WaywardRT)
  find_package(WaywardRT REQUIRED)
endif()

if(NOT TARGET GTest::gtest)
  find_package(GTest CONFIG REQUIRED)
endif()

set(WaywardRT_TEST_SOURCE_FILES
  src/QuaternionTest.cpp
  src/RayTest.cpp
  src/Vec3Test.cpp
)

add_executable(WaywardRTAllTests ${WaywardRT_TEST_SOURCE_FILES})
target_link_libraries(WaywardRTAllTests WaywardRT GTest::gtest_main)

set_target_properties(WaywardRTAllTests PROPERTIES
  CXX_STANDARD               17
  CXX_VISIBILITY_PRESET      hidden
  VISIBILITY_INLINES_HIDDEN  YES
)

if(WaywardRT_APPLY_CPPLINT AND NOT WaywardRT_CPPLINT_FILEPATH STREQUAL "")
  set_target_properties(WaywardRTAllTests
    PROPERTIES
      CXX_CPPLINT ${WaywardRT_CPPLINT_FILEPATH}
  )
endif()

if(MSVC)
  target_compile_options(WaywardRTAllTests PRIVATE /W4 /WX)
else()
  target_compile_options(WaywardRTAllTests PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-result)
endif()

foreach(TEST_FILE IN LISTS WaywardRT_TEST_SOURCE_FILES)
  get_filename_component(TEST_TARGET ${TEST_FILE} NAME_WE)
  add_executable(${TEST_TARGET} ${TEST_FILE})
  target_link_libraries(${TEST_TARGET} WaywardRT GTest::gtest_main)

  set_target_properties(${TEST_TARGET} PROPERTIES
    CXX_STANDARD               17
    CXX_VISIBILITY_PRESET      hidden
    VISIBILITY_INLINES_HIDDEN  YES
  )

  if(MSVC)
    target_compile_options(${TEST_TARGET} PRIVATE /W4 /WX)
  else()
    target_compile_options(${TEST_TARGET} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-result)
  endif()

endforeach()
