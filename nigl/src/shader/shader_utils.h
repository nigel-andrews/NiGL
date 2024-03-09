#pragma once

#include <filesystem>
#include <string>

namespace nigl::shader
{
    std::string get_shader_source(const std::filesystem::path& shader_path);
} // namespace nigl::shader
