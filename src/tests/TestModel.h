#pragma once

#include "Test.h"
#include "defines.h"

namespace test {

    class TestModel : public Test
    {
    public:
        TestModel();
        ~TestModel();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera& camera) override;
        void OnImGuiRender() override;
    private:

    private:
        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation;
        std::vector<glm::vec3> m_CubePositions{};
        std::vector<glm::vec3> m_LightPositions{};
    };
}