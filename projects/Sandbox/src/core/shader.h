#pragma once
#include <vector>
#include <string>
#include <vmath.h>


enum class ShaderTypeE
{
    NONE, VERTEX, TESSELATION_CONTROL,
    TESSELATION_EVALUATION, FRAGMENT,
    GEOMETRY, COMPUTE
};


struct ShaderOptions
{
    ShaderOptions(const std::string &filepath, ShaderTypeE type):
    filepath(filepath), type(type)
    {}

    ShaderOptions(const ShaderOptions &opts)
    {
        filepath = opts.filepath;
        type = opts.type;
    }

    std::string GetDebugStr() const;

    std::string filepath;
    ShaderTypeE type;
};


class Shader
{
    public:
    Shader(const std::vector<ShaderOptions> &opts);
    ~Shader();

    void Bind();
    void UnBind();

    void SetUniform(const char *name, int value);
    void SetUniform(const char *name, float value);
    void SetUniform(const char *name, const vmath::vec2 &vec2);
    void SetUniform(const char *name, const vmath::vec3 &vec3);
    void SetUniform(const char *name, const vmath::vec4 &vec4);
    void SetUniform(const char *name, const vmath::mat2 &mat2);
    void SetUniform(const char *name, const vmath::mat4 &mat4);

    std::string GetFilename(ShaderTypeE shader_type);
    std::string GetDebugStr();

    private:
    unsigned int m_id;
    std::vector<ShaderOptions> m_shaderOptions;

    unsigned int CreateCompileShader(const char *source, unsigned int type);
    unsigned int CreateLinkProgram(const std::vector<unsigned int> &shaders);
    std::string ReadSourceFromFile(const char *filename);
};
