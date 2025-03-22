#pragma once
#include <string>

class Lesson
{
    friend class Sandbox;

    public:
    Lesson(const std::string &name);
    virtual ~Lesson();

    virtual void onStart();
    virtual void onUpdate(double currentTime, double deltaTime);

    inline std::string getName() const {return m_name;}

    private:
    bool m_hasStarted;
    std::string m_name;
};