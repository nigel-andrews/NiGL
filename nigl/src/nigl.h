#pragma once

class GLFWwindow;

namespace nigl
{
    GLFWwindow* init_glfw();
    void init_glad();
    void main_loop(GLFWwindow* window);
} // namespace nigl
