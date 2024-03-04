add_executable(demo main.cpp)

target_include_directories(demo PUBLIC ../src)

target_link_libraries(demo PRIVATE compile_options nigl)
