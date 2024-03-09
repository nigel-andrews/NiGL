set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.90.1)

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

add_executable(demo main.cpp)

target_include_directories(demo PUBLIC ../nigl/src)

target_link_libraries(demo PRIVATE compile_options nigl)
