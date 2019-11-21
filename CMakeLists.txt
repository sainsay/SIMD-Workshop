cmake_minimum_required(VERSION 3.13)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${curdir}/${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


project( SIMDWorkshop )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_NAME "SIMD_workshop")

#files
file(GLOB_RECURSE MATH_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/quick_math/*.hpp")
file(GLOB_RECURSE MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/quick_math/*.cpp")

#projects
add_library(QuickMath STATIC ${MATH_HEADERS} ${MATH_SOURCES})
set_target_properties(QuickMath PROPERTIES CXX_STANDARD 17)
set_target_properties(QuickMath PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(QuickMath PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_options(QuickMath PRIVATE /W4 /WX /permissive- /MP /Gm-) #msvc only
target_include_directories(QuickMath PUBLIC ${CMAKE_SOURCE_DIR}/src/utility_lib/include)

SUBDIRLIST(SUBDIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/")
FOREACH(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
ENDFOREACH()


