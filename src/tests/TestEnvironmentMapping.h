#pragma once
#include "defines.h"
#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"

namespace test
{
    class TestEnvironmentMapping : public Test
    {
    public:
        TestEnvironmentMapping();
        ~TestEnvironmentMapping();

        void OnUpdate(float deltaTime) override;
        void OnRender(Camera &camera) override;
        void OnImGuiRender() override;

    private:
        uint32_t m_CubemapTexture;
        std::unordered_map<std::string, uint32_t> m_SkyboxTextureDictionary;

        std::unique_ptr<Shader> m_CubeShader;
        std::unique_ptr<VertexArray> m_CubeVAO;
        std::unique_ptr<VertexBuffer> m_CubeVBO;
        std::unique_ptr<Texture> m_CubeTexture;

        std::unique_ptr<Shader> m_SkyboxShader;
        std::unique_ptr<VertexArray> m_SkyBoxVAO;
        std::unique_ptr<VertexBuffer> m_SkyBoxVBO;
    };
}