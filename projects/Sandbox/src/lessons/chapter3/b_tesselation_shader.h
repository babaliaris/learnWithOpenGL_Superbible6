#pragma once
#include "../../core/lesson.h"
#include <core/shader.h>

class TesselationShader : public Lesson
{
    public:
    TesselationShader();
    ~TesselationShader();

    void onStart() override;
    void onUpdate(double currentTime, double deltaTime) override;

    private:
    unsigned int m_vao;
    Shader *m_shader;

};