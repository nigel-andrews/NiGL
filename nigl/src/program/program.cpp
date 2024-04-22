#include "program.h"

#include <unordered_map>

#include "shader_utils.h"

namespace nigl
{
    namespace
    {
        // TODO: Replace variants with expected when supported
        GLint compile_and_attach_shader(
            int program_id, GLenum shader_type,
            const std::filesystem::path& shader_source_path)
        {
            auto shader_id = glCreateShader(shader_type);

            auto source = get_shader_source(shader_source_path);

            auto source_cstr = source.c_str();
            glShaderSource(shader_id, 1, &source_cstr, nullptr);

            glCompileShader(shader_id);
            glAttachShader(program_id, shader_id);

            return shader_id;
        }
    } // namespace

    Program::Program()
        : id_(glCreateProgram())
    {
        if (!this->id_)
        {
            throw std::runtime_error("Failed to create shader program");
        }
    }

    // TODO: clean up everything chacal
    Program::~Program() = default;

    Program& Program::add_shader_source(const fs::path& shader_source_path,
                                        GLenum shader_type)
    {
        // TODO: Check if this works
        static std::unordered_map<GLenum, std::optional<GLuint> Program::*> lut{
            { GL_VERTEX_SHADER, &Program::vertex_id_ },
            { GL_FRAGMENT_SHADER, &Program::fragment_id_ },
            { GL_TESS_CONTROL_SHADER, &Program::tessellation_control_ },
            { GL_TESS_EVALUATION_SHADER, &Program::tessellation_eval_ },
            { GL_GEOMETRY_SHADER, &Program::geometry_id_ },
        };

        this->*lut[shader_type] =
            compile_and_attach_shader(id_, shader_type, shader_source_path);

        return *this;
    }

    void Program::link_program()
    {
        glLinkProgram(id_);

        // FIXME: Detach and delete shaders (cleanup quoi.)
    }

    Program Program::from_files(const ShaderConfig&)
    {
        throw std::logic_error("Not implemented");
    }

    Program Program::from_files(const ComputeShaderConfig&)
    {
        throw std::logic_error("Not implemented");
    }
} // namespace nigl
