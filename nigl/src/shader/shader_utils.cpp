#include "shader_utils.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

namespace nigl::shader
{
    namespace
    {
        std::optional<std::string>
        process_include(const std::string& line,
                        const std::filesystem::path& folder)
        {
            std::stringstream include(line);

            include.ignore(line.size(), ' ');
            if (include.fail() || include.eof())
            {
                std::cerr
                    << "Failed to parse include " << line
                    << " : missing space between directive and filename\n";
                return std::nullopt;
            }

            std::string filename;
            include >> filename;

            if (include.fail())
            {
                std::cerr << "Failed to parse include " << line
                          << " : No filename was found\n";
                return std::nullopt;
            }

            filename = filename.substr(1);
            while (filename.back() == ' ' || filename.back() == '"')
                filename.pop_back();

            return get_shader_source(folder / filename);
        }
    } // namespace

    std::string get_shader_source(const std::filesystem::path& shader_path)
    {
        std::stringstream source;
        std::ifstream file(shader_path);
        std::filesystem::path shader_folder = shader_path.parent_path();

        for (std::string line; std::getline(file, line);)
        {
            if (line.find("#include") != line.npos)
                source << process_include(line, shader_folder).value_or("")
                       << '\n';
            else
                source << line << '\n';
        }

        return source.str();
    }
} // namespace nigl::shader
