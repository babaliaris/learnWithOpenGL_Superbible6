#pragma once
#include "../../core/lesson.h"

class OurFirstApplication : public Lesson
{
    public:
    OurFirstApplication();
    ~OurFirstApplication();

    void onStart() override;
    void onUpdate(double currentTime, double deltaTime) override;
};