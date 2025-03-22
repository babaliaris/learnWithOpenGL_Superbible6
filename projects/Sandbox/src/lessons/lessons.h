#pragma once
#include <iostream>
#include "chapter2/our_first_application.h"

enum class LessonE
{
    NONE, CHAPTER2_OUR_FIRST_APPLICATION
};

Lesson *GetLesson(LessonE lesson)
{
    switch (lesson)
    {
        case LessonE::CHAPTER2_OUR_FIRST_APPLICATION:
            return new OurFirstApplication();
        
        default:
            printf("[GetLesson()] Uknown Lesson, exiting...");
            return nullptr;
    }
}