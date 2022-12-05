#pragma once

#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

    class TestBlend : public Test
    {
    public:
        TestBlend();
        ~TestBlend();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera& camera) override;
        void OnImGuiRender() override;
    private:
        std::unordered_map<std::string, std::string> m_ShaderMap;
        std::string m_ActiveShader;
        std::unique_ptr<Shader> m_Shader;

        std::unique_ptr<VertexArray> m_CubeVAO;
        std::unique_ptr<VertexBuffer> m_CubeVBO;
        std::unique_ptr<Texture> m_CubeTexture;
        
        std::unique_ptr<VertexArray> m_PlaneVAO;
        std::unique_ptr<VertexBuffer> m_PlaneVBO;
        std::unique_ptr<Texture> m_PlaneTexture;

        std::unique_ptr<Texture> m_WindowsTexture;
        std::vector<glm::vec3> windows;
        std::unique_ptr<VertexArray> m_WindowsVAO;
        std::unique_ptr<VertexBuffer> m_WindowsVBO;

        std::map<float, glm::vec3> m_Sorted;
    };
}

