#include "nigl.h"

int main(int, char**)
{
    auto window = nigl::init_glfw();
    nigl::init_glad();

    nigl::main_loop(window);

    return 0;
}
