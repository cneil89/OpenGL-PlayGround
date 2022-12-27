#pragma once

#include "Test.h"
#include "defines.h"
#include "Model.h"

namespace test
{

    class TestModel : public Test
    {
    public:
        TestModel();
        ~TestModel();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera &camera) override;
        void OnImGuiRender() override;

    private:
        void SetPointLightProps(uint32_t index);

    private:
        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation;

        std::vector<glm::vec3> m_LightPositions;

        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Shader> m_LightCubeShader;
        Model m_Model;
    };
}