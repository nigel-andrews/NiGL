#pragma once

#include <filesystem>
#include <string>

namespace shader
{
    std::string get_shader_source(const std::filesystem::path& shader_path);
} // namespace shader
