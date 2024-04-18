#pragma once

#include <iostream>

#define GL(Expr, ...)                                                          \
    do                                                                         \
    {                                                                          \
        (Expr);                                                                \
        if (glGetError() != GL_NO_ERROR)                                       \
        {                                                                      \
            std::cerr << "Failed calling " << #Expr << " line: " << __LINE__   \
                      << " in file: " << __FILE__ << "\n";                     \
            __VA_ARGS__;                                                       \
        }                                                                      \
    } while (false)
