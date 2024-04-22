#pragma once

#include <filesystem>
#include <glad/glad.h>

#include "shader_config.h"
#include "utils/traits.h"

namespace nigl
{
    // FIXME: Create a IProgram interface and have ShaderProgram and
    // ComputeProgram implement it
    class Program : public NonCopyable
    {
    public:
        Program();
        ~Program();

        Program(Program&& rhs);
        Program operator=(Program&& rhs);

        Program& add_shader_source(const fs::path& shader_source_path,
                                   GLenum shader_type);

        void link_program();
        void use_program();

        static Program from_files(const ShaderConfig& shader_config);
        static Program from_files(const ComputeShaderConfig& shader_config);

    private:
        GLuint id_;

        std::optional<GLuint> vertex_id_;
        std::optional<GLuint> geometry_id_;
        std::optional<GLuint> tessellation_control_;
        std::optional<GLuint> tessellation_eval_;
        std::optional<GLuint> fragment_id_;
    };
}; // namespace nigl
