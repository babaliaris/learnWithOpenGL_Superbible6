#include "shader.h"
#include "glcall.h"
#include <GL/gl3w.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>


GLenum GetShaderGLType(ShaderTypeE shader_type);
ShaderTypeE GetShaderTypeFromGLType(GLenum shader_type);
std::string GetShaderTypeToStr(ShaderTypeE type);


Shader::Shader(const std::vector<ShaderOptions> &opts)
: m_id(0), m_shaderOptions(opts)
{
    std::vector<unsigned int> shaders;

    //Read all the shaders from the files and compile them.
    for (ShaderOptions opt : m_shaderOptions)
    {
        std::string source = ReadSourceFromFile(opt.filepath.c_str());

        shaders.push_back( CreateCompileShader(source.c_str(), GetShaderGLType(opt.type)) );
    }

    m_id = CreateLinkProgram(shaders);
}

Shader::~Shader()
{
    glCall(glDeleteProgram(m_id));
}

void Shader::Bind()
{
    glCall(glUseProgram(m_id));
}

void Shader::UnBind()
{
    glCall(glUseProgram(0));
}

void Shader::SetUniform(const char *name, int value)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniform1i(loc, value));

    this->UnBind();
}


void Shader::SetUniform(const char *name, float value)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniform1f(loc, value));

    this->UnBind();
}


void Shader::SetUniform(const char *name, const vmath::vec2 &vec2)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniform2fv(loc, 1, &vec2[0]));

    this->UnBind();
}


void Shader::SetUniform(const char *name, const vmath::vec3 &vec3)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniform3fv(loc, 1, &vec3[0]));

    this->UnBind();
}


void Shader::SetUniform(const char *name, const vmath::vec4 &vec4)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniform4fv(loc, 1, &vec4[0]));

    this->UnBind();
}


void Shader::SetUniform(const char *name, const vmath::mat2 &mat2)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniformMatrix2fv(loc, 1, GL_FALSE, &mat2[0][0]));

    this->UnBind();
}


void Shader::SetUniform(const char *name, const vmath::mat4 &mat4)
{
    this->Bind();

    glCall(GLint loc = glGetUniformLocation(m_id, name));

    if (loc < 0)
    {
        printf("[Uniform Upload Error]\n%s\tReason: Uniform \"%s\", was not found!\n", GetDebugStr().c_str(), name);
        return;
    }

    glCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &mat4[0][0]));

    this->UnBind();
}


std::string Shader::GetFilename(ShaderTypeE shader_type)
{
    for (ShaderOptions opt :  m_shaderOptions)
    {
        if (shader_type == opt.type)
            return opt.filepath;
    }

    return "";
}


std::string Shader::GetDebugStr()
{
    std::stringstream ss;

    for (ShaderOptions opt : m_shaderOptions)
    {
        ss << "\t" << opt.GetDebugStr() << std::endl;
    }

    return ss.str();
}


std::string ShaderOptions::GetDebugStr() const
{
    std::stringstream ss;

    ss << "Shader(" << GetShaderTypeToStr(type) << "): " << filepath;

    return ss.str();
}


unsigned int Shader::CreateCompileShader(const char *source, GLenum type)
{
    GLuint shader = glCreateShader(type);

    glCall(glShaderSource(shader, 1, &source, NULL));

    glCall(glCompileShader(shader));

    GLint info_length, success;

    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length));


    if (!success)
    {
        std::string filename = GetFilename( GetShaderTypeFromGLType(type) );

        char *info = new char[info_length];

        glCall(glGetShaderInfoLog(shader, info_length, NULL, info));

        printf("[Shader Compilation Error]: %s\n\tReason: %s\n", filename.c_str(), info);

        delete info;

        return 0;
    }

    return shader;
}


unsigned int Shader::CreateLinkProgram(const std::vector<unsigned int> &shaders)
{
    //Create the program.
    glCall(GLuint program = glCreateProgram());

    //Attach all the shaders.
    for (unsigned int shader : shaders)
    {
        glCall(glAttachShader(program, shader));
    }

    //Link the program.
    glCall(glLinkProgram(program));

    //Check for linkage errros.
    GLint info_length, success;
    glCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
    glCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length));
    if (!success)
    {
        char *info = new char[info_length];

        glCall(glGetProgramInfoLog(program, info_length, NULL, info));

        std::cout << "[Program Linkage Error]\n" << info << std::endl;

        delete info;

        glCall(glDeleteProgram(program));

        program = 0;
    }

    //Delete all the shaders.
    for (unsigned int shader : shaders)
    {
        glCall(glDeleteShader(shader));
    }

    return program;
}



std::string Shader::ReadSourceFromFile(const char *filename)
{
    std::ifstream file(filename, std::ios::binary);
    std::stringstream ss;

    if (!file.is_open())
    {
        std::cout << "Failed to open File: " << filename << std::endl;
        return "";
    }

    ss << file.rdbuf();

    return ss.str();
}



GLenum GetShaderGLType(ShaderTypeE shader_type)
{
    switch (shader_type)
    {
        case ShaderTypeE::VERTEX:
            return GL_VERTEX_SHADER;

        case ShaderTypeE::TESSELATION_CONTROL:
            return GL_TESS_CONTROL_SHADER;

        case ShaderTypeE::TESSELATION_EVALUATION:
            return GL_TESS_EVALUATION_SHADER;

        case ShaderTypeE::GEOMETRY:
            return GL_GEOMETRY_SHADER;

        case ShaderTypeE::FRAGMENT:
            return GL_FRAGMENT_SHADER;

        case ShaderTypeE::COMPUTE:
            return GL_COMPUTE_SHADER;

        default:
            return GL_NONE;
    }
}


ShaderTypeE GetShaderTypeFromGLType(GLenum shader_type)
{
    switch (shader_type)
    {
        case GL_VERTEX_SHADER:
            return ShaderTypeE::VERTEX;

        case GL_TESS_CONTROL_SHADER:
            return ShaderTypeE::TESSELATION_CONTROL;

        case GL_TESS_EVALUATION_SHADER:
            return ShaderTypeE::TESSELATION_EVALUATION;

        case GL_GEOMETRY_SHADER:
            return ShaderTypeE::GEOMETRY;

        case GL_FRAGMENT_SHADER:
            return ShaderTypeE::FRAGMENT;

        case GL_COMPUTE_SHADER:
            return ShaderTypeE::COMPUTE;

        default:
            return ShaderTypeE::NONE;
    }
}

std::string GetShaderTypeToStr(ShaderTypeE type)
{
    switch (type)
    {
        case ShaderTypeE::VERTEX:
            return "VER";

        case ShaderTypeE::TESSELATION_CONTROL:
            return "TCS";

        case ShaderTypeE::TESSELATION_EVALUATION:
            return "TES";

        case ShaderTypeE::GEOMETRY:
            return "GEO";

        case ShaderTypeE::FRAGMENT:
            return "FRA";

        case ShaderTypeE::COMPUTE:
            return "COM";
        
        default:
            return "NONE";
    }
}
