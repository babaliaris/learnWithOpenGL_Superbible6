#include "b_using_shaders.h"
#include <sb6.h>
#include <math.h>

UsingShaders::UsingShaders():
Lesson("UsingShaders")
{
}


UsingShaders::~UsingShaders()
{

}

void UsingShaders::onStart()
{

}


void UsingShaders::onUpdate(double currentTime, double deltaTime)
{
    const GLfloat red[] = {
        (float)cos(currentTime) * 0.5f + 0.5f,
        (float)sin(currentTime) * 0.5f + 0.5f,
        0.0f,
        1.0f
    };

    glClearBufferfv(GL_COLOR, 0, red);
}