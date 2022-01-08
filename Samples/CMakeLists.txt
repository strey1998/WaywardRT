cmake_minimum_required(VERSION 3.10)

set(WaywardRT_Sample_SOURCE_FILES
  src/Sample.cpp
)

foreach(SAMPLE_FILE IN LISTS WaywardRT_Sample_SOURCE_FILES)
  get_filename_component(SAMPLE_TARGET ${SAMPLE_FILE} NAME_WE)
  add_executable(${SAMPLE_TARGET} ${SAMPLE_FILE})
  target_link_libraries(${SAMPLE_TARGET} WaywardRT)

  if(MSVC)
    target_compile_options(${SAMPLE_TARGET} PRIVATE /W4 /WX)
  else()
    target_compile_options(${SAMPLE_TARGET} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-result)
  endif()

  if(WaywardRT_APPLY_CPPLINT AND NOT WaywardRT_CPPLINT_FILEPATH STREQUAL "")
    set_target_properties(${SAMPLE_TARGET}
      PROPERTIES
        CXX_CPPLINT ${WaywardRT_CPPLINT_FILEPATH}
    )
  endif()

endforeach()
