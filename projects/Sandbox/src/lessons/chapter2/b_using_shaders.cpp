#include "b_using_shaders.h"
#include <sb6.h>
#include <math.h>

GLuint CreateProgram(const GLchar *const *vertexSrc, const GLchar *const *fragSrc);

UsingShaders::UsingShaders():
Lesson("UsingShaders")
{
}


UsingShaders::~UsingShaders()
{
    glDeleteProgram(m_program);
    glDeleteVertexArrays(1, &m_vao);
}

void UsingShaders::onStart()
{
    const GLchar *vertexSource[] = {
        "#version 430 core\n"
        "void main(void)"
        "{"
            "gl_Position = vec4(0.0, 0.0, 0.5, 1.0);"
        "}"
    };

    const GLchar * fragmentSource[] = {
        "#version 430 core\n"
        "out vec4 color;"
        "void main(void)"
        "{"
            "color = vec4(0.0, 0.8, 1.0, 1.0);"
        "}"
    };

    m_program = CreateProgram(vertexSource, fragmentSource);

    glGenVertexArrays(1, &m_vao);

    glPointSize(45.0f);
}


void UsingShaders::onUpdate(double currentTime, double deltaTime)
{
    const GLfloat color[] = {
        (float)cos(currentTime) * 0.5f + 0.5f,
        (float)sin(currentTime) * 0.5f + 0.5f,
        0.0f,
        1.0f
    };

    glClearBufferfv(GL_COLOR, 0, color);

    glBindVertexArray(m_vao);
    glUseProgram(m_program);
    glDrawArrays(GL_POINTS, 0, 1);
}


GLuint CompileShader(const GLchar *const *source, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    
    glShaderSource(shader, 1, source, NULL);

    glCompileShader(shader);

    GLint success, length_info;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length_info);

    if (!success)
    {
        char *info = new char[length_info];

        glGetShaderInfoLog(shader, length_info, NULL, info);

        std::string shaderTypeStr = (shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");

        printf("[%s Shader Compilation FAILED] %s\n", shaderTypeStr.c_str(), info);

        delete info;

        return 0;
    }

    return shader;
}



GLuint CreateProgram(const GLchar *const *vertexSrc, const GLchar *const *fragSrc)
{
    GLuint vertexShader = CompileShader(vertexSrc, GL_VERTEX_SHADER);
    GLuint fragShader = CompileShader(fragSrc, GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    GLint success, length_info;

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length_info);

    if (!success)
    {
        char *info = new char[length_info];

        glGetProgramInfoLog(program, length_info, NULL, info);

        printf("[Program Linkage FAILED] %s\n", info);

        delete info;

        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    return program;
}