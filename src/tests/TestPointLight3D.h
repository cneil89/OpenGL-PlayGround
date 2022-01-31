#pragma once
#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

    class TestPointLight3D : public Test
    {
    public:
        TestPointLight3D();
        ~TestPointLight3D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        void GenerateCube();
        float randomNum(float min, float max);
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexArray> m_LightVAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Shader> m_LightCubeShader;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Texture> m_Texture2;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation;
        glm::vec3 m_LightPos;
        std::vector<glm::vec3> m_CubePositions = {{0.0f, 0.0f, 0.0f}};
    };
}