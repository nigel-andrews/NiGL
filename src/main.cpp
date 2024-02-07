#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "utils/wrappers.h"

namespace
{
    void init_glfw()
    {
        glfwSetErrorCallback([](int code, const char* msg) {
            std::cerr << "Error " << code << "\n\tReason: " << msg << "\n";
        });

        if (auto err = (glfwInit()); err != GLFW_TRUE)
        {
            GLFW_ERR(glfwInit);
        }

        std::cout << "Initialized GLFW...\n";
    }

    void init_glew()
    {
        if (auto err = (glewInit()); err != GLEW_OK)
        {
            std::cerr << "Failed calling glewInit()\n";
            std::cerr << "\tReason: " << glewGetErrorString(err) << "\n";
            std::exit(1);
        }

        std::cout << "Initialized GLEW...\n";
    }
} // namespace

int main(int, char**)
{
    init_glfw();
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    glfwMakeContextCurrent(window);

    init_glew();

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    return 0;
}
