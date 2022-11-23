#pragma once
#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace test {

    class TestDepth : public Test
    {
    public:
        TestDepth();
        ~TestDepth();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera& camera) override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_CubeVAO;
        std::unique_ptr<VertexBuffer> m_CubeVBO;
        std::unique_ptr<VertexArray> m_PlaneVAO;
        std::unique_ptr<VertexBuffer> m_PlaneVBO;
    };
}