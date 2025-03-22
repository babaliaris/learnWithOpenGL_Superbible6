#include "glcall.h"
#include <iostream>
#include <GL/freeglut.h>

const char *GetGLerrorMeaning(GLenum err)
{
    switch (err)
    {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";

        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";

        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";

        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";

        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";

        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";

        case GL_TABLE_TOO_LARGE:
            return "GL_TABLE_TOO_LARGE";

        default:
            return "Uknown OpenGL Error";
    }
}

void __ClearAllErrors__()
{
    while (glGetError());
}


void __GetAllErrors__(const char *file, long long line)
{
    while (GLenum err = glGetError())
    {
        printf("[OpenGL Error: %s (%d)]\n\tFile: %s\n\tLine: %d\n", GetGLerrorMeaning(err), err, file, line);
    }
}
