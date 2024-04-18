add_library(program STATIC program.cpp shader_utils.cpp)

set_target_properties(program PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)

target_link_libraries(program PRIVATE compile_options glad)
