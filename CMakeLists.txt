cmake_minimum_required(VERSION 3.20)

project(NiGL)

add_library(compile_options INTERFACE)

target_compile_options(
  compile_options
  INTERFACE "-Wall"
            "-Wextra"
            "-Wvla"
            "-pedantic"
            $<$<CONFIG:Release>:-O3>
            $<$<CONFIG:Release>:-Werror>
            $<$<CONFIG:Debug>:-O0>
            $<$<CONFIG:Debug>:-fno-inline>
            $<$<CONFIG:Debug>:-g3>
            $<$<CONFIG:Debug>:-fsanitize=address>)

target_link_options(compile_options INTERFACE
                    $<$<CONFIG:Debug>:-fsanitize=address>)

target_compile_definitions(compile_options INTERFACE -DDEBUG)

add_subdirectory(src)

add_executable(nigl src/main.cpp)

set_target_properties(nigl PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)

target_link_libraries(nigl PRIVATE compile_options)
