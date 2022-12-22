#pragma once
#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

    class TestFramebuffer : public Test
    {
    public:
        TestFramebuffer();
        ~TestFramebuffer();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera& camera) override;
        void OnImGuiRender() override;
    private:
        std::unordered_map<std::string, std::string> m_ShaderMap;
        std::string m_ActiveShader;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Shader> m_ScreenShader;

        uint32_t m_Fbo;  // Framebuffer
        uint32_t m_Tcb;  // TextureColorBuffer
        uint32_t m_Rbo; // Renderbuffer object

        std::unique_ptr<VertexArray> m_CubeVAO;
        std::unique_ptr<VertexBuffer> m_CubeVBO;
        std::unique_ptr<Texture> m_CubeTexture;
        
        std::unique_ptr<VertexArray> m_PlaneVAO;
        std::unique_ptr<VertexBuffer> m_PlaneVBO;
        std::unique_ptr<Texture> m_PlaneTexture;
        
        std::unique_ptr<VertexArray> m_QuadVAO;
        std::unique_ptr<VertexBuffer> m_QuadVBO;
        std::unique_ptr<Texture> m_QuadTexture;
        
    };
}

