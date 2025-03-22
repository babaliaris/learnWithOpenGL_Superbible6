#pragma once
#include "../../core/lesson.h"

class DrawingOurFirstTriangle : public Lesson
{
    public:
    DrawingOurFirstTriangle();
    ~DrawingOurFirstTriangle();

    void onStart() override;
    void onUpdate(double currentTime, double deltaTime) override;

    private:
    unsigned int m_program, m_vao;
};