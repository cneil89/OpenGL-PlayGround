#pragma once
#include "defines.h"
#include "Camera.h"

namespace test
{
    class Test
    {
    public:
        Test(std::string name) : m_TestName(name) {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender(Camera &camera) {}
        virtual void OnImGuiRender() {}
        virtual std::string getTestName() { return m_TestName; }

    private:
        std::string m_TestName;
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test *&currentTestPointer);

        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string &name)
        {
            std::cout << "Registering Test -> " << name << std::endl;

            m_Tests.push_back(std::make_pair(name, []()
                                             { return new T(); }));
        }

    private:
        Test *&m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
    };
}