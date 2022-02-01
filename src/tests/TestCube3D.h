#pragma once
#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

    class TestCube3D : public Test
    {
    public:
        TestCube3D();
        ~TestCube3D();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera& camera) override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Texture> m_Texture2;

        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation;
    };
}