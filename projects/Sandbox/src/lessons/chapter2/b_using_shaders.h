#pragma once
#include "../../core/lesson.h"

class UsingShaders : public Lesson
{
    public:
    UsingShaders();
    ~UsingShaders();

    void onStart() override;
    void onUpdate(double currentTime, double deltaTime) override;

    private:
    unsigned int m_program, m_vao;
};