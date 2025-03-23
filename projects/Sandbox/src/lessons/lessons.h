#pragma once
#include <iostream>
#include "chapter2/a_our_first_application.h"
#include "chapter2/b_using_shaders.h"
#include "chapter2/c_drawing_our_first_triangle.h"
#include "chapter3/a_vertex_attributes.h"
#include "chapter3/b_tesselation_shader.h"
#include "chapter3/c_tesselation_and_geometry.h"

enum class LessonE
{
    NONE, CHAPTER2_OUR_FIRST_APPLICATION,
    CHAPTER2_USING_SHADERS,
    CHAPTER2_DRAWING_OUR_FIRST_TRIANGLE,
    CHAPTER3_VERTEX_ATTRIBUTES,
    CHAPTER3_TESSELATION_SHADER,
    CHAPTER3_TESSELATION_AND_GEOMETRY
};

Lesson *GetLesson(LessonE lesson)
{
    switch (lesson)
    {
        case LessonE::CHAPTER3_TESSELATION_AND_GEOMETRY:
            return new TesselationAndGeometry();

        case LessonE::CHAPTER3_TESSELATION_SHADER:
            return new TesselationShader();

        case LessonE::CHAPTER3_VERTEX_ATTRIBUTES:
            return new VertexAttributes();

        case LessonE::CHAPTER2_DRAWING_OUR_FIRST_TRIANGLE:
            return new DrawingOurFirstTriangle();

        case LessonE::CHAPTER2_USING_SHADERS:
            return new UsingShaders();

        case LessonE::CHAPTER2_OUR_FIRST_APPLICATION:
            return new OurFirstApplication();
        
        default:
            printf("[GetLesson()] Uknown Lesson, exiting...");
            return nullptr;
    }
}