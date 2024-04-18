#pragma once

#include <filesystem>
#include <glad/glad.h>

#include "shader_config.h"
#include "utils/traits.h"

namespace nigl
{
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

        static Program from_files(const ShaderConfig& shader_config);
        static Program from_files(const ComputeShaderConfig& shader_config);

    private:
        GLuint id_;

        // FIXME: use optionals to preserve invariants
        GLuint vertex_id_;
        GLuint geometry_id_;
        GLuint tessellation_control_;
        GLuint tessellation_eval_;
        GLuint fragment_id_;
    };
}; // namespace nigl
