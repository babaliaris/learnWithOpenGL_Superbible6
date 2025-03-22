#include "lesson.h"

Lesson::Lesson(const std::string &name):
m_hasStarted(false), m_name(name)
{
}


Lesson::~Lesson()
{
}

void Lesson::onStart()
{
}


void Lesson::onUpdate(double currentTime, double deltaTime)
{
}