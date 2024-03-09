#pragma once

#include <concepts>
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

namespace nigl::shader
{
    struct ShaderConfig
    {
        fs::path vertex_shader;
        std::optional<fs::path> tess_control_shader = std::nullopt;
        std::optional<fs::path> tess_eval_shader = std::nullopt;
        std::optional<fs::path> geometry_shader = std::nullopt;
        fs::path fragment_shader;
    };

    struct ComputeShaderConfig
    {
        fs::path compute_shader;
    };

    template <typename T>
    concept Configurable = std::convertible_to<T, ShaderConfig>
        || std::convertible_to<T, ComputeShaderConfig>;
} // namespace nigl::shader
