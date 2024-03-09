#pragma once

#include <glad/glad.h>

#include "shader/shader_config.h"

namespace nigl
{
    GLint create_program(const nigl::shader::ShaderConfig& config);
    GLint create_program(const nigl::shader::ComputeShaderConfig& config);
}; // namespace nigl
