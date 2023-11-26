#include "TestCubemap.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "stb/stb_image.h"
#include "imgui/imgui.h"

namespace test
{
    TestCubemap::TestCubemap()
        : Test("Cubemap")
    {
        glEnable(GL_DEPTH_TEST);
        float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
        float skyboxVertices[] = {
            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f};

        m_SkyboxTextureDictionary["Skyscape"] = Texture::LoadCubemap({"../res/textures/skybox1/right.jpg",
                                                                      "../res/textures/skybox1/left.jpg",
                                                                      "../res/textures/skybox1/top.jpg",
                                                                      "../res/textures/skybox1/bottom.jpg",
                                                                      "../res/textures/skybox1/front.jpg",
                                                                      "../res/textures/skybox1/back.jpg"});

        m_SkyboxTextureDictionary["Cityscape"] = Texture::LoadCubemap({"../res/textures/skybox2/right.jpg",
                                                                       "../res/textures/skybox2/left.jpg",
                                                                       "../res/textures/skybox2/top.jpg",
                                                                       "../res/textures/skybox2/bottom.jpg",
                                                                       "../res/textures/skybox2/front.jpg",
                                                                       "../res/textures/skybox2/back.jpg"});

        m_SkyboxTextureDictionary["Space"] = Texture::LoadCubemap({"../res/textures/skybox3/right.png",
                                                                   "../res/textures/skybox3/left.png",
                                                                   "../res/textures/skybox3/top.png",
                                                                   "../res/textures/skybox3/bottom.png",
                                                                   "../res/textures/skybox3/front.png",
                                                                   "../res/textures/skybox3/back.png"});

        m_CubemapTexture = m_SkyboxTextureDictionary["Skyscape"];

        m_CubeShader = std::make_unique<Shader>("../res/shaders/OGLBookDepthTesting.shader");
        m_CubeVAO = std::make_unique<VertexArray>();
        m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float));
        VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(3);
        cubeLayout.Push<float>(2);
        m_CubeVAO->AddBuffer(*m_CubeVBO, cubeLayout);
        m_CubeTexture = std::make_unique<Texture>("../res/textures/container.jpg");
        m_CubeTexture->Bind(0);

        m_SkyboxShader = std::make_unique<Shader>("../res/shaders/OGLBookSkyBox.shader");
        m_SkyBoxVAO = std::make_unique<VertexArray>();
        m_SkyBoxVBO = std::make_unique<VertexBuffer>(skyboxVertices, 36 * 3 * sizeof(float));
        VertexBufferLayout skyboxLayout;
        skyboxLayout.Push<float>(3);
        m_SkyBoxVAO->AddBuffer(*m_SkyBoxVBO, skyboxLayout);

        m_CubeShader->Bind();
        m_CubeShader->SetUniform1i("texture1", 0);
        m_SkyboxShader->Bind();
        m_SkyboxShader->SetUniform1i("skybox", 0);
    }

    TestCubemap::~TestCubemap()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestCubemap::OnUpdate(float deltaTime)
    {
    }

    void TestCubemap::OnRender(Camera &camera)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer renderer;
        m_CubeTexture->Bind(0);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        m_CubeShader->Bind();
        m_CubeShader->SetUniformMat4f("model", model);
        m_CubeShader->SetUniformMat4f("view", view);
        m_CubeShader->SetUniformMat4f("projection", projection);
        m_CubeShader->SetUniform1i("texture1", 0);
        renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

        // skybox
        glDepthFunc(GL_LEQUAL);
        m_SkyboxShader->Bind();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        m_SkyboxShader->SetUniformMat4f("view", view);
        m_SkyboxShader->SetUniformMat4f("projection", projection);
        m_SkyBoxVAO->Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubemapTexture);
        renderer.Draw(*m_SkyBoxVAO, *m_SkyboxShader, 36);
        m_SkyBoxVAO->Unbind();
        glDepthFunc(GL_LESS);
    }

    void TestCubemap::OnImGuiRender()
    {
        for (auto &item : m_SkyboxTextureDictionary)
            if (ImGui::RadioButton(item.first.c_str(), m_CubemapTexture == item.second))
                m_CubemapTexture = item.second;
    }
}