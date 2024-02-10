#pragma once

#include <variant>

#include "shader/shader_config.h"

class Program
{
public:
    explicit Program(shader::ShaderConfig&& config)
        : config_(config)
    {}

    explicit Program(shader::ComputeShaderConfig&& config)
        : config_(config)
    {}

private:
    std::variant<shader::ShaderConfig, shader::ComputeShaderConfig> config_;
};
