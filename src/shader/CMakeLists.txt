add_library(shader STATIC shader_utils.cpp)

set_target_properties(shader PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_link_libraries(shader PRIVATE compile_options)
