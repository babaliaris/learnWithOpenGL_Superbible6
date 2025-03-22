#pragma once
#include <iostream>
#include "chapter2/a_our_first_application.h"
#include "chapter2/b_using_shaders.h"

enum class LessonE
{
    NONE, CHAPTER2_OUR_FIRST_APPLICATION,
    CHAPTER2_USING_SHADERS
};

Lesson *GetLesson(LessonE lesson)
{
    switch (lesson)
    {
        case LessonE::CHAPTER2_USING_SHADERS:
            return new UsingShaders();

        case LessonE::CHAPTER2_OUR_FIRST_APPLICATION:
            return new OurFirstApplication();
        
        default:
            printf("[GetLesson()] Uknown Lesson, exiting...");
            return nullptr;
    }
}