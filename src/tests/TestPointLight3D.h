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
        void OnRender(Camera& camera) override;
        void OnImGuiRender() override;

    private:
        void GenerateCube();
        float randomNum(float min, float max);
        
        // TODO: Part out into its own class to be used by whole applicaiton
        // Should likely pass in shader reference/pointer as well a predefined struct(?)
        void SetPointLightProps(uint32_t index);
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
        std::vector<glm::vec3> m_CubePositions{{0.0f, 0.0f, 0.0f}};
        std::vector<glm::vec3> m_LightPositions{glm::vec3{1.5f, 1.5f, 0.0f}};
    };
}