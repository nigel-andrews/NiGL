#include "nigl.h"
#include "program/program.h"

int main(int, char**)
{
    auto window = nigl::init_glfw();
    nigl::init_glad();

    nigl::Program program;

    program.add_shader_source("demo/shaders/vertex.glsl", GL_VERTEX_SHADER)
        .link_program();

    nigl::main_loop(window);

    return 0;
}
