#include "nigl.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <format>
#include <iostream>
#include <unordered_map>

#include "utils/keyboard.h"

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

    // Thank you https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f
    // for the possible values
    void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                        GLsizei /*length*/, const GLchar* msg,
                        const void* /*data*/)
    {
        static const std::unordered_map<GLenum, const char*> sources{
            { GL_DEBUG_SOURCE_API, "API" },
            { GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WINDOW_SYSTEM" },
            { GL_DEBUG_SOURCE_SHADER_COMPILER, "SHADER_COMPILER" },
            { GL_DEBUG_SOURCE_THIRD_PARTY, "THIRD_PARTY" },
            { GL_DEBUG_SOURCE_APPLICATION, "APPLICATION" },
            { GL_DEBUG_SOURCE_OTHER, "UNKNOWN" },
        };

        static const std::unordered_map<GLenum, const char*> types{
            { GL_DEBUG_TYPE_ERROR, "ERROR" },
            { GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED_BEHAVIOR" },
            { GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "UNDEFINED_BEHAVIOR" },
            { GL_DEBUG_TYPE_PORTABILITY, "PORTABILITY" },
            { GL_DEBUG_TYPE_PERFORMANCE, "PERFORMANCE" },
            { GL_DEBUG_TYPE_OTHER, "OTHER" },
            { GL_DEBUG_TYPE_MARKER, "MARKER" },
        };

        static const std::unordered_map<GLenum, const char*> severities{
            { GL_DEBUG_SEVERITY_LOW, "LOW" },
            { GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM" },
            { GL_DEBUG_SEVERITY_HIGH, "HIGH" },
            { GL_DEBUG_SEVERITY_NOTIFICATION, "NOTIFICATION" },
        };

        auto source_it = sources.find(source);
        auto type_it = types.find(type);
        auto severity_it = severities.find(severity);

        constexpr auto unwrap = [](const auto& value, const auto& past_end) {
            if (value != past_end)
            {
                return value->second;
            }

            return "UNKNOWN";
        };

        std::cerr << std::format("ERROR[{}][{}] {} ! From {} : {}\n", id,
                                 unwrap(severity_it, severities.end()),
                                 unwrap(type_it, types.end()),
                                 unwrap(source_it, sources.end()), msg);
    }

    void init_glad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        // FIXME: let the user toggle this feature (with custom formatting ?)
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(nullptr, nullptr);

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
