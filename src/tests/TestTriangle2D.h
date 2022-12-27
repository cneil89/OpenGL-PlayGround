#pragma once
#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace test
{

    class TestTriangle2D : public Test
    {
    public:
        TestTriangle2D();
        ~TestTriangle2D();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera &camera) override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation;
    };
}