cmake_minimum_required(VERSION 3.13)
message("Hello world!1")
#files
file(GLOB_RECURSE EXAMPLE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#projects
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
add_executable(${ProjectId} WIN32 ${EXAMPLE_HEADERS} ${EXAMPLE_SOURCES})
set_target_properties(${ProjectId} PROPERTIES CXX_STANDARD 17)
set_target_properties(${ProjectId} PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(${ProjectId} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(${ProjectId} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/../")

#msvc only
set_target_properties(${ProjectId} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
set_target_properties(${ProjectId} PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
set_target_properties(${ProjectId} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
set_target_properties(${ProjectId} PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
set_target_properties(${ProjectId} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
set_target_properties(${ProjectId} PROPERTIES COMPILE_DEFINITIONS_RELEASE "_CONSOLE")
set_target_properties(${ProjectId} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE")
set_target_properties(${ProjectId} PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL "_CONSOLE")

target_compile_options(${ProjectId} PRIVATE /W4 /WX /permissive- /MP /Gm-) #msvc only

target_include_directories(${ProjectId} PUBLIC ${CMAKE_SOURCE_DIR}/src/quick_math)

target_link_libraries(${ProjectId} QuickMath)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${ProjectId})
