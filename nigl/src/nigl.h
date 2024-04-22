#pragma once

class GLFWwindow;

// TODO: Not sure if this is the best way to handle an entry point. Might go for
// an Application class w/ virtual functions so overriding the class allows to
// implement the logic ?
namespace nigl
{
    GLFWwindow* init_glfw();
    void init_glad();
    void main_loop(GLFWwindow* window);
} // namespace nigl
