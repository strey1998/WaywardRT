cmake_minimum_required(VERSION 3.10)

set(WaywardRT_Sample_INCLUDE_DIRS
)

set(WaywardRT_Sample_SOURCE_FILES
  src/main.cpp
)

add_executable(WaywardRTSample_Main ${WaywardRT_Sample_SOURCE_FILES})
target_include_directories(WaywardRTSample_Main PRIVATE ${WaywardRT_Sample_INCLUDE_DIRS})
target_link_libraries(WaywardRTSample_Main PRIVATE WaywardRT)

if(WaywardRT_APPLY_CPPLINT AND NOT WaywardRT_CPPLINT_FILEPATH STREQUAL "")
  set_target_properties(WaywardRTSample_Main
    PROPERTIES
      CXX_CPPLINT ${WaywardRT_CPPLINT_FILEPATH}
  )
endif()

if(MSVC)
  target_compile_options(WaywardRTSample_Main PRIVATE /W4 /WX)
else()
  target_compile_options(WaywardRTSample_Main PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-result)
endif()
