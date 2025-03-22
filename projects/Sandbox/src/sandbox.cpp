#include <sb6.h>
#include "lessons/lessons.h"

class Sandbox : public sb6::application
{
    public:
    Sandbox():
    m_currentFrame(0.0f), m_lastFrame(0.0f), m_deltaTime(0.0f),
    m_lesson( GetLesson(LessonE::CHAPTER2_USING_SHADERS) )
    {
    }

    ~Sandbox()
    {
        delete m_lesson;
    }


    void render(double currentTime)
    {
        m_currentFrame  = currentTime;
        m_deltaTime     = m_currentFrame - m_lastFrame;
        m_lastFrame     = m_currentFrame;

        //On Start.
        if (!m_lesson->m_hasStarted)
        {
            glfwSetWindowTitle(m_lesson->getName().c_str());
            printf("[System]: Running Lesson \"%s\"\n", m_lesson->getName().c_str());
            m_lesson->onStart();
            m_lesson->m_hasStarted = true;
        }

        //On Updated.
        else
        {
            m_lesson->onUpdate(currentTime, m_deltaTime);
        }
    }

    private:
    double m_currentFrame, m_lastFrame, m_deltaTime;
    Lesson *m_lesson;
};


DECLARE_MAIN(Sandbox);