#pragma once
#include "../../core/lesson.h"
#include <core/shader.h>

class TesselationAndGeometry : public Lesson
{
    public:
    TesselationAndGeometry();
    ~TesselationAndGeometry();

    void onStart() override;
    void onUpdate(double currentTime, double deltaTime) override;

    private:
    unsigned int m_vao;
    Shader *m_shader;

};