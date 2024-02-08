// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

#include "utils/wrappers.h"

namespace
{
    int width = 800;
    int height = 600;

    void init_glfw()
    {
        glfwSetErrorCallback([](int code, const char* msg) {
            std::cerr << "Error " << code << "\n\tReason: " << msg << "\n";
        });

        if (auto err = (glfwInit()); err != GLFW_TRUE)
            GLFW_ERR(glfwInit);

        std::cout << "Initialized GLFW...\n";
    }

    void init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        GL(glViewport(0, 0, width, height));

        std::cout << "Initialized GLAD...\n";
    }
} // namespace

int main(int, char**)
{
    init_glfw();

    GLFWwindow* window = glfwCreateWindow(width, height, "NiGL", NULL, NULL);
    glfwSetFramebufferSizeCallback(window,
                                   [](GLFWwindow*, int width, int height) {
                                       glViewport(0, 0, width, height);
                                   });

    if (!window)
        GLFW_ERR(glfwCreateWindow);

    glfwMakeContextCurrent(window);

    init_glad();

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
