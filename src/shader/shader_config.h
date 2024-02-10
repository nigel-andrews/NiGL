#pragma once

#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

namespace shader
{
    struct ShaderConfig
    {
        fs::path vertex_shader;
        std::optional<fs::path> tess_control_shader;
        std::optional<fs::path> tess_eval_shader;
        std::optional<fs::path> geometry_shader;
        fs::path fragment_shader;
    };

    struct ComputeShaderConfig
    {
        fs::path compute_shader;
    };
} // namespace shader
