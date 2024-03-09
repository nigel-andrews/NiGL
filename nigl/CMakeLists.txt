set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_GetProperties(imgui)

set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_INSTALL
    OFF
    CACHE BOOL "" FORCE)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.9)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.0)

FetchContent_MakeAvailable(glm)

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

add_subdirectory(external)

add_subdirectory(src)

add_library(nigl SHARED src/nigl.cpp)

target_compile_options(nigl PRIVATE "-fPIC")

set_target_properties(nigl PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_include_directories(nigl PUBLIC external)

target_link_libraries(nigl PRIVATE compile_options imgui glfw glad glm::glm
                                   shader)
