add_library(shader STATIC shader_utils.cpp)

target_link_libraries(shader PRIVATE compile_options)
