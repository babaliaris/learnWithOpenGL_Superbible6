#include "c_drawing_our_first_triangle.h"
#include <sb6.h>
#include <math.h>
#include <core/glcall.h>

static GLuint CreateProgram(const GLchar *const *vertexSrc, const GLchar *const *fragSrc);

DrawingOurFirstTriangle::DrawingOurFirstTriangle():
Lesson("DrawingOurFirstTriangle")
{
}


DrawingOurFirstTriangle::~DrawingOurFirstTriangle()
{
    glCall(glDeleteProgram(m_program));
    glCall(glDeleteVertexArrays(1, &m_vao));
}

void DrawingOurFirstTriangle::onStart()
{
    const GLchar *vertexSource[] = {
        "#version 430 core\n"
        "void main(void)\n"
        "{\n"
            "// Declare a hard-coded array of positions\n"
            "const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),\n"
            "vec4(-0.25, -0.25, 0.5, 1.0),\n"
            "vec4( 0.25, 0.25, 0.5, 1.0));\n"
            "gl_Position = vertices[gl_VertexID];\n"
        "}\n"
    };

    const GLchar * fragmentSource[] = {
        "#version 430 core\n"
        "out vec4 color;\n"
        "void main(void)\n"
        "{\n"
            "color = vec4(0.0, 0.8, 1.0, 1.0);\n"
        "}\n"
    };

    m_program = CreateProgram(vertexSource, fragmentSource);

    glCall(glGenVertexArrays(1, &m_vao));

    glCall(glPointSize(45.0f));
}


void DrawingOurFirstTriangle::onUpdate(double currentTime, double deltaTime)
{
    const GLfloat color[] = {
        (float)cos(currentTime) * 0.5f + 0.5f,
        (float)sin(currentTime) * 0.5f + 0.5f,
        0.0f,
        1.0f
    };

    glCall(glClearBufferfv(GL_COLOR, 0, color));

    glCall(glBindVertexArray(m_vao));
    glCall(glUseProgram(m_program));
    glCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}


static GLuint CompileShader(const GLchar *const *source, GLenum shader_type)
{
    GLuint shader = glCreateShader(shader_type);
    
    glCall(glShaderSource(shader, 1, source, NULL));

    glCall(glCompileShader(shader));

    GLint success, length_info;

    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length_info));

    if (!success)
    {
        char *info = new char[length_info];

        glCall(glGetShaderInfoLog(shader, length_info, NULL, info));

        std::string shaderTypeStr = (shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");

        printf("[%s Shader Compilation FAILED] %s", shaderTypeStr.c_str(), info);

        delete info;

        return 0;
    }

    return shader;
}



static GLuint CreateProgram(const GLchar *const *vertexSrc, const GLchar *const *fragSrc)
{
    GLuint vertexShader = CompileShader(vertexSrc, GL_VERTEX_SHADER);
    GLuint fragShader = CompileShader(fragSrc, GL_FRAGMENT_SHADER);

    glCall(GLuint program = glCreateProgram());

    glCall(glAttachShader(program, vertexShader));
    glCall(glAttachShader(program, fragShader));

    glCall(glLinkProgram(program));

    GLint success, length_info;

    glCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
    glCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length_info));

    if (!success)
    {
        char *info = new char[length_info];

        glCall(glGetProgramInfoLog(program, length_info, NULL, info));

        printf("[Program Linkage FAILED] %s", info);

        delete info;

        glDeleteProgram(program);
        program = 0;
    }

    glCall(glDeleteShader(vertexShader));
    glCall(glDeleteShader(fragShader));

    return program;
}