#pragma once
#include "../../core/lesson.h"

class TesselationShader : public Lesson
{
    public:
    TesselationShader();
    ~TesselationShader();

    void onStart() override;
    void onUpdate(double currentTime, double deltaTime) override;

    private:
    unsigned int m_program, m_vao;
};