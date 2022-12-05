#include "TestBlend.h"

#include "imgui/imgui.h"

namespace test {

    TestBlend::TestBlend()
        : Test("Blending")
    {

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
        m_ShaderMap["Blending"] = "res/shaders/OGLBookBlending.shader";

        m_ActiveShader = m_ShaderMap["Blending"];
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
        m_PlaneTexture = std::make_unique<Texture>("res/textures/wood_planks.png");
        m_PlaneTexture->Bind(1);

        windows.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
        windows.push_back(glm::vec3( 1.5f, 0.0f,  0.51f));
        windows.push_back(glm::vec3( 0.0f, 0.0f,  0.7f));
        windows.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
        windows.push_back(glm::vec3( 0.5f, 0.0f, -0.6f));

        float WindowsVert[] = {
            // positions             // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
            0.0f,  0.5f,  0.0f,      0.0f,  0.0f,
            0.0f, -0.5f,  0.0f,      0.0f,  1.0f,
            1.0f, -0.5f,  0.0f,      1.0f,  1.0f,
    
            0.0f,  0.5f,  0.0f,      0.0f,  0.0f,
            1.0f, -0.5f,  0.0f,      1.0f,  1.0f,
            1.0f,  0.5f,  0.0f,      1.0f,  0.0f							
        };  
        m_WindowsVAO = std::make_unique<VertexArray>();
        m_WindowsVBO = std::make_unique<VertexBuffer>(WindowsVert, 6 * 5 * sizeof(float));
        VertexBufferLayout WindowsLayout;
        WindowsLayout.Push<float>(3);
        WindowsLayout.Push<float>(2);
        m_WindowsVAO->AddBuffer(*m_WindowsVBO, WindowsLayout);
        m_WindowsTexture = std::make_unique<Texture>("res/textures/window.png", true);
        m_WindowsTexture->Bind(2);


    }

    TestBlend::~TestBlend()
    {
        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
    }

    void TestBlend::OnUpdate(float deltaTime) 
    {

    }

    void TestBlend::OnRender(Camera& camera) 
    {
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (size_t i = 0; i < windows.size(); ++i)
        {
            float distance = glm::length2(camera.GetPosition() - windows[i]);
            m_Sorted[distance] = windows[i];
        }

        m_CubeTexture->Bind(0);
        m_PlaneTexture->Bind(1);
        m_WindowsTexture->Bind(2);


        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);

        m_PlaneVAO->Bind();
        m_Shader->SetUniform1i("texture1", 1);
        m_Shader->SetUniformMat4f("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        m_PlaneVAO->Unbind();

        m_CubeVAO->Bind();
        m_Shader->SetUniform1i("texture1", 0);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_Shader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        m_Shader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        m_WindowsVAO->Bind();
        m_Shader->SetUniform1i("texture1", 2);
        for(std::map<float, glm::vec3>::reverse_iterator it = m_Sorted.rbegin(); it != m_Sorted.rend(); ++it)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, it->second);
            m_Shader->SetUniformMat4f("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        m_Sorted.clear();

    }

    void TestBlend::OnImGuiRender() 
    {
        for (auto &item : m_ShaderMap)
            if(ImGui::RadioButton(item.first.c_str(), m_ActiveShader == item.second)) 
            {
                m_ActiveShader = item.second;
                m_Shader = std::make_unique<Shader>(m_ActiveShader);
            }
    }
}