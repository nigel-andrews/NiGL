#pragma once

// Required for the macro when in debug mode
#include <iostream>

#define GLFW_ERR(Func)                                                         \
    do                                                                         \
    {                                                                          \
        std::cerr << "Failed calling " << #Func << " line: " << __LINE__       \
                  << " in file: " << __FILE__ << "\n";                         \
        const char* msg = nullptr;                                             \
        glfwGetError(&msg);                                                    \
        std::cerr << "\tReason: " << msg << std::endl;                         \
        std::exit(1);                                                          \
    } while (false)

#define GL(Expr, ...)                                                          \
    do                                                                         \
    {                                                                          \
        (Expr);                                                                \
        if (glGetError() != GL_NO_ERROR)                                       \
        {                                                                      \
            std::cerr << "Failed calling " << #Expr << " line: " << __LINE__   \
                      << " in file: " << __FILE__ << "\n";                     \
            std::exit(1);                                                      \
        }                                                                      \
        __VA_ARGS__;                                                           \
    } while (false)
