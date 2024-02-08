cmake_minimum_required(VERSION 3.20)

project(NiGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.1)

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

if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui)
  set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR}/)
  file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)
  file(GLOB IMGUI_HEADERS ${imgui_SOURCE_DIR}/*.h)
  add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_SOURCES})
  add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

  target_include_directories(
    imgui PUBLIC ${IMGUI_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIR}
                 ${GLAD_INCLUDE_DIR})
  target_link_libraries(imgui ${OPENGL_LIBRARIES} glfw GLEW)
endif()

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

add_executable(nigl src/main.cpp)

set_target_properties(nigl PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)

target_link_libraries(nigl PRIVATE compile_options imgui glfw glad glm::glm)
