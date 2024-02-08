#pragma once

// Required for the macro when in debug mode

#define GLFW_ERR(Func)                                                         \
    do                                                                         \
    {                                                                          \
        const char* msg = nullptr;                                             \
        glfwGetError(&msg);                                                    \
        throw std::runtime_error(msg);                                         \
    } while (false)

#define GL(Expr, ...)                                                          \
    do                                                                         \
    {                                                                          \
        (Expr);                                                                \
        if (glGetError() != GL_NO_ERROR)                                       \
        {                                                                      \
            std::cerr << "Failed calling " << #Expr << " line: " << __LINE__   \
                      << " in file: " << __FILE__ << "\n";                     \
        }                                                                      \
        __VA_ARGS__;                                                           \
    } while (false)
