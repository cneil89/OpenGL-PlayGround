#pragma once
#include "defines.h"
#include "glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    uint32_t m_RendererID;
    mutable std::unordered_map<std::string, int32_t> m_UniformLocationCache;

public:
    Shader(const std::string &filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    uint32_t GetID() { return m_RendererID; }

    // Set uniforms
    void SetUniform1i(const std::string &name, int32_t value);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);
    void SetUniformVec3f(const std::string &name, const glm::vec3 &vector);
    void SetUniformVec3f(const std::string &name, float x, float y, float z);

private:
    ShaderProgramSource ParseShader(const std::string &filepath);
    uint32_t CompileShader(uint32_t type, const std::string &source);
    uint32_t CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    int32_t GetUniformLocation(const std::string &name) const;
};