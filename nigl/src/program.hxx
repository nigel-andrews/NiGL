#pragma once

#include <vector>

#include "program.h"
#include "shader/shader_utils.h"
#include "utils/wrappers.h"

namespace Program
{
    namespace
    {
        inline GLint compile_and_attach_shader(
            int program_id, int shader_type,
            const std::filesystem::path& shader_source_path)
        {
            GLint shader_id;
            GL(shader_id = glCreateShader(shader_type), return -1);

            std::string shader_source =
                shader::get_shader_source(shader_source_path);

            const char* shader_source_cstr = shader_source.c_str();

            GL(glShaderSource(shader_id, 1, &shader_source_cstr, nullptr),
               glDeleteShader(shader_id);
               return -1);

            GL(glCompileShader(shader_id), glDeleteShader(shader_id);
               return -1);

            GL(glAttachShader(program_id, shader_id), glDeleteShader(shader_id);
               return -1);

            return shader_id;
        }

    } // namespace

    GLint create_program(const shader::Configurable auto& config)
    {
        if constexpr (std::convertible_to<decltype(config),
                                          shader::ComputeShaderConfig>)
        {
            GLint program_id;
            GL(program_id = glCreateProgram());

            auto shader_id = compile_and_attach_shader(
                program_id, GL_COMPUTE_SHADER, config.compute_shader);

            GL(glLinkProgram(program_id));

            GL(glDetachShader(program_id, shader_id));
            GL(glDeleteShader(shader_id));

            return program_id;
        }

        GLint program_id;

        GL(program_id = glCreateProgram());

        if (!program_id)
            return -1;

        std::vector<GLint> shader_ids;
        shader_ids.reserve(5);

        if (GLint shader_id = compile_and_attach_shader(
                program_id, GL_VERTEX_SHADER, config.vertex_shader);
            shader_id != -1)
            shader_ids.push_back(shader_id);

        if (GLint shader_id = compile_and_attach_shader(
                program_id, GL_FRAGMENT_SHADER, config.fragment_shader);
            shader_id != -1)
            shader_ids.push_back(shader_id);

        if (config.tess_control_shader.has_value())
        {
            GLint shader_id =
                compile_and_attach_shader(program_id, GL_TESS_CONTROL_SHADER,
                                          config.tess_control_shader.value());
            if (shader_id != -1)
                shader_ids.push_back(shader_id);
        }

        if (config.tess_eval_shader.has_value())
        {
            GLint shader_id =
                compile_and_attach_shader(program_id, GL_TESS_EVALUATION_SHADER,
                                          config.tess_eval_shader.value());
            if (shader_id != -1)
                shader_ids.push_back(shader_id);
        }

        if (config.geometry_shader.has_value())
        {
            GLint shader_id = compile_and_attach_shader(
                program_id, GL_GEOMETRY_SHADER, config.geometry_shader.value());
            if (shader_id != -1)
                shader_ids.push_back(shader_id);
        }

        GL(glLinkProgram(program_id));

        for (const auto id : shader_ids)
        {
            GL(glDetachShader(program_id, id));
            GL(glDeleteShader(id));
        }

        return program_id;
    }
} // namespace Program
