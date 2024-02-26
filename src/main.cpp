// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

#include "program.h"
#include "utils/wrappers.h"

namespace
{
    int window_width = 800;
    int window_height = 600;

    GLFWwindow* init_glfw()
    {
        glfwSetErrorCallback([](int code, const char* msg) {
            std::cerr << "Error " << code << "\n\tReason: " << msg << "\n";
        });

        if (auto err = (glfwInit()); err != GLFW_TRUE)
            GLFW_ERR(glfwTerminate();
                     throw std::runtime_error("Failed to initialize GLFW"));

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        std::cout << "Initialized GLFW...\n";
        GLFWwindow* window =
            glfwCreateWindow(window_width, window_height, "NiGL", NULL, NULL);

        if (!window)
            GLFW_ERR(glfwTerminate();
                     throw std::runtime_error("Failed to create window"));

        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window,
                                       [](GLFWwindow*, int width, int height) {
                                           GL(glViewport(0, 0, width, height));
                                           window_width = width;
                                           window_height = height;
                                       });

        glfwSetKeyCallback(window,
                           [](GLFWwindow* window, int key, int /* scancode */,
                              int /* action */, int /* mods */) {
                               if (key == GLFW_KEY_ESCAPE)
                                   glfwSetWindowShouldClose(window, true);
                           });

        glfwSwapInterval(1);

        return window;
    }

    void init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        std::cout << "Renderer: " << glGetString(GL_RENDERER)
                  << "\nOpenGL version: " << glGetString(GL_VERSION) << "\n";

        GL(glViewport(0, 0, window_width, window_height));

        std::cout << "Initialized GLAD...\n";
    }
} // namespace

int main(int, char**)
{
    auto window = init_glfw();

    init_glad();

    while (!glfwWindowShouldClose(window))
    {
        GL(glClear(GL_COLOR_BUFFER_BIT));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
