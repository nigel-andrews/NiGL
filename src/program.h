#pragma once

#include <glad/glad.h>

#include "shader/shader_config.h"

namespace Program
{
    GLint create_program(const shader::Configurable auto& config);
}; // namespace Program

#include "program.hxx"
