#include "nigl.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

#include "program/program.h"
#include "utils/keyboard.h"
#include "utils/wrappers.h"

#define GLFW_ERR(...)                                                          \
    do                                                                         \
    {                                                                          \
        const char* msg = nullptr;                                             \
        glfwGetError(&msg);                                                    \
        __VA_ARGS__;                                                           \
    } while (false)

namespace nigl
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
                                           glViewport(0, 0, width, height);
                                           window_width = width;
                                           window_height = height;
                                       });

        glfwSetKeyCallback(window,
                           [](GLFWwindow* window, int key, int /* scancode */,
                              int /* action */, int /* mods */) {
                               if (key == GLFW_KEY_ESCAPE)
                                   glfwSetWindowShouldClose(window, true);

                               if (UP)
                               {
                                   std::cout << "Up\n";
                               }
                               if (DOWN)
                               {
                                   std::cout << "Down\n";
                               }
                               if (LEFT)
                               {
                                   std::cout << "Left\n";
                               }
                               if (RIGHT)
                               {
                                   std::cout << "Right\n";
                               }
                           });

        glfwSwapInterval(1);

        return window;
    }

#undef GLFW_ERR

    void init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

#ifdef DEBUG
        // FIXME: let the user toggle this feature (with custom formatting ?)
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(nullptr, nullptr);
#endif // DEBUG

        std::cout << "Renderer: " << glGetString(GL_RENDERER)
                  << "\nOpenGL version: " << glGetString(GL_VERSION) << "\n";

        glViewport(0, 0, window_width, window_height);

        std::cout << "Initialized GLAD...\n";
    }

    void main_loop(GLFWwindow* window)
    {
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }
} // namespace nigl
