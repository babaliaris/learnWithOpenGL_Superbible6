#include "our_first_application.h"
#include <sb6.h>
#include <math.h>

OurFirstApplication::OurFirstApplication():
Lesson("OurFirstApplication")
{
}


OurFirstApplication::~OurFirstApplication()
{

}

void OurFirstApplication::onStart()
{

}


void OurFirstApplication::onUpdate(double currentTime, double deltaTime)
{
    const GLfloat red[] = {
        (float)cos(currentTime) * 0.5f + 0.5f,
        (float)sin(currentTime) * 0.5f + 0.5f,
        0.0f,
        1.0f
    };

    glClearBufferfv(GL_COLOR, 0, red);
}