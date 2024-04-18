add_library(glad STATIC src/glad.c)

set_target_properties(glad PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF)
target_compile_options(glad PRIVATE -fPIC)

target_include_directories(glad PUBLIC include)
target_include_directories(compile_options INTERFACE include)
