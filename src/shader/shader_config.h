#pragma once

#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

namespace shader
{
    struct shader_config
    {
        fs::path vertex_shader;
        std::optional<fs::path> tess_control_shader;
        std::optional<fs::path> tess_eval_shader;
        fs::path fragment_shader;
    };

    struct compute_shader_config
    {
        fs::path compute_shader;
    };
} // namespace shader
