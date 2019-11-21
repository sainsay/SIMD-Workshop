cmake_minimum_required(VERSION 3.13)

project( SIMDWorkshop )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_NAME "SIMD_workshop")

#files
file(GLOB_RECURSE MATH_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/quick_math/*.hpp")
file(GLOB_RECURSE MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/quick_math/*.cpp")
file(GLOB_RECURSE EXAMPLE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/*.hpp")
file(GLOB_RECURSE EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/examples/*.cpp")

#projects
add_library(QuickMath STATIC ${MATH_HEADERS} ${MATH_SOURCES})
set_target_properties(QuickMath PROPERTIES CXX_STANDARD 17)
set_target_properties(QuickMath PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(QuickMath PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_options(QuickMath PRIVATE /W4 /WX /permissive- /MP /Gm-) #msvc only
target_include_directories(QuickMath PUBLIC ${CMAKE_SOURCE_DIR}/src/utility_lib/include)

add_executable(ExampleApp WIN32 ${EXAMPLE_HEADERS} ${EXAMPLE_SOURCES})
set_target_properties(ExampleApp PROPERTIES CXX_STANDARD 17)
set_target_properties(ExampleApp PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(ExampleApp PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(ExampleApp PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/../")

#msvc only
set_target_properties(ExampleApp PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
set_target_properties(ExampleApp PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
set_target_properties(ExampleApp PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
set_target_properties(ExampleApp PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
set_target_properties(ExampleApp PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
set_target_properties(ExampleApp PROPERTIES COMPILE_DEFINITIONS_RELEASE "_CONSOLE")
set_target_properties(ExampleApp PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
set_target_properties(ExampleApp PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL "_CONSOLE")

target_compile_options(ExampleApp PRIVATE /W4 /WX /permissive- /MP /Gm-) #msvc only

target_include_directories(ExampleApp PUBLIC ${CMAKE_SOURCE_DIR}/src/quick_math/include)

target_link_libraries(ExampleApp QuickMath)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ExampleApp)

#projects grouping
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(uninstall PROPERTIES FOLDER CMakePredefinedTargets)
