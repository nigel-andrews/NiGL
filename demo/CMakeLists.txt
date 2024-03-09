set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(demo main.cpp)

target_include_directories(demo PUBLIC ../nigl/src)

target_link_libraries(demo PRIVATE nigl)
