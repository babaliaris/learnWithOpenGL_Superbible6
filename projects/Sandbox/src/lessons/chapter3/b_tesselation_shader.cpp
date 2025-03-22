#include "b_tesselation_shader.h"
#include <sb6.h>
#include <math.h>
#include <core/glcall.h>



TesselationShader::TesselationShader():
Lesson("Tesselation Shader")
{
}


TesselationShader::~TesselationShader()
{
    delete m_shader;
    glCall(glDeleteVertexArrays(1, &m_vao));
}

void TesselationShader::onStart()
{
    std::vector<ShaderOptions> opts = {
        {"projects/Sandbox/src/shaders/chapter3/b_tesselation_shader.v.glsl", ShaderTypeE::VERTEX},
        {"projects/Sandbox/src/shaders/chapter3/b_tesselation_shader.f.glsl", ShaderTypeE::FRAGMENT}
    };

    m_shader = new Shader(opts);

    m_shader->SetUniform("asdasd", 10);

    glCall(glGenVertexArrays(1, &m_vao));

    glCall(glPointSize(45.0f));
}


void TesselationShader::onUpdate(double currentTime, double deltaTime)
{   

    //Clear Color.
    const GLfloat clear_color[] = {
        (float)sin(currentTime) * 0.5f + 0.5f,
        (float)cos(currentTime) * 0.5f + 0.5f,
        0.0f,
        1.0f
    };

    //Triangle Color (Clear color reversed).
    const GLfloat triangle_color[] = {
        (float)cos(currentTime) * 0.5f + 0.5f,
        (float)sin(currentTime) * 0.5f + 0.5f,
        0.0f,
        1.0f
    };

    //Create the offset position to represent a circle.
    //This will animate the triangle like it moves in a circle.
    const GLfloat offset[] = {
        (float)cos(currentTime) * 0.8f,
        (float)sin(currentTime) * 0.8f,
        0.0f,
        1.0f
    };

    //Set and update the attributes every frame!!!
    glCall(glVertexAttrib4fv(0, offset)); //Set the value of the attributes with index=0
    glCall(glVertexAttrib4fv(1, triangle_color)); //Set the color attribute.

    //Clear the screen before drawing.
    glCall(glClearBufferfv(GL_COLOR, 0, clear_color));

    //Draw Call.
    m_shader->Bind();
    glCall(glBindVertexArray(m_vao));
    glCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}
