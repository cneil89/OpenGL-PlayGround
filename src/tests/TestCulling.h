#pragma once

#include "defines.h"
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {

    class TestCulling : public Test
    {
    public:
        TestCulling();
        ~TestCulling();

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
        
    };
}

