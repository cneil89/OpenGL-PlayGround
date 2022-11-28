#include "TestDepth.h"
#include "imgui/imgui.h"

namespace test {

    TestDepth::TestDepth()
    {

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        float cubeVertices[] = {
            // positions             // texture Coords
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f
        };
        float planeVertices[] = {
             // positions             // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,     2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,     0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,     0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,     2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,     0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,     2.0f, 2.0f								
        };
        m_ShaderMap["Texture"] = "res/shaders/OGLBookDepthTesting.shader";
        m_ShaderMap["Depth Test"] = "res/shaders/OGLBookDepthTesting2.shader";

        m_ActiveShader = m_ShaderMap["Texture"];
        m_Shader = std::make_unique<Shader>(m_ActiveShader);
        
        //CUBE
        m_CubeVAO = std::make_unique<VertexArray>();
        m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float));
        VertexBufferLayout CubeLayout;
        CubeLayout.Push<float>(3);
        CubeLayout.Push<float>(2);
        m_CubeVAO->AddBuffer(*m_CubeVBO, CubeLayout);
        m_CubeTexture = std::make_unique<Texture>("res/textures/marble.jpg");
        m_CubeTexture->Bind(0);

        //Plane
        m_PlaneVAO = std::make_unique<VertexArray>();
        m_PlaneVBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 5 * sizeof(float));
        VertexBufferLayout PlaneLayout;
        PlaneLayout.Push<float>(3);
        PlaneLayout.Push<float>(2);
        m_PlaneVAO->AddBuffer(*m_PlaneVBO, PlaneLayout);
        m_PlaneTexture = std::make_unique<Texture>("res/textures/metal.png");
        m_PlaneTexture->Bind(1);

    }

    TestDepth::~TestDepth()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestDepth::OnUpdate(float deltaTime) 
    {

    }

    void TestDepth::OnRender(Camera& camera) 
    {
        glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_CubeTexture->Bind(0);
        m_PlaneTexture->Bind(1);

        m_Shader->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_CubeVAO->Bind();
        m_Shader->SetUniform1i("texture1", 0);
        m_Shader->SetUniformMat4f("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        m_PlaneVAO->Bind();
        m_Shader->SetUniform1i("texture1", 1);
        m_Shader->SetUniformMat4f("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0 ,36);
    }

    void TestDepth::OnImGuiRender() 
    {
        for (auto &item : m_ShaderMap)
            if(ImGui::RadioButton(item.first.c_str(), m_ActiveShader == item.second)) 
            {
                m_ActiveShader = item.second;
                m_Shader = std::make_unique<Shader>(m_ActiveShader);
            }
    }
}