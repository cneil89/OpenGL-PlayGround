#include "TestStencil.h"

#include "imgui/imgui.h"

namespace test {

    TestStencil::TestStencil()
        : Test("Stencil Test"),
            m_Scale(1.07f)
    {

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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
        m_ShaderMap["Texture"] = "res/shaders/OGLBookStencil.shader";

        m_ActiveShader = m_ShaderMap["Texture"];
        m_Shader = std::make_unique<Shader>(m_ActiveShader);
        m_SingleColorShader = std::make_unique<Shader>("res/shaders/OGLBookStencilSingleColor.shader");
        
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

    TestStencil::~TestStencil()
    {
        glDisable(GL_STENCIL_TEST);
        glDisable(GL_DEPTH_TEST);
    }

    void TestStencil::OnUpdate(float deltaTime) 
    {

    }

    void TestStencil::OnRender(Camera& camera) 
    {
        glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        m_CubeTexture->Bind(0);
        m_PlaneTexture->Bind(1);

        m_SingleColorShader->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_SingleColorShader->SetUniformMat4f("view", view);
        m_SingleColorShader->SetUniformMat4f("projection", projection);

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);

        glStencilMask(0x00);
        m_PlaneVAO->Bind();
        m_Shader->SetUniform1i("texture1", 1);
        m_Shader->SetUniformMat4f("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        m_PlaneVAO->Unbind();



        // 1st. render pass, draw objects as normal, writing to the stencil buffer
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        m_CubeVAO->Bind();
        m_Shader->SetUniform1i("texture1", 0);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        m_Shader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        m_Shader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
        // Because the stencil buffer is now filled with several 1s. The parts of the buffer that are 1 are not drawn, thus only drawing 
        // the objects' size differences, making it look like borders.
        // -----------------------------------------------------------------------------------------------------------------------------
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0xFF);

        glDisable(GL_DEPTH_TEST);
        m_SingleColorShader->Bind();
        m_CubeVAO->Bind();
        // m_Shader->SetUniform1i("texture1", 0);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(m_Scale, m_Scale, m_Scale));
        m_SingleColorShader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(m_Scale, m_Scale, m_Scale));
        m_SingleColorShader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        m_CubeVAO->Unbind();
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

    }

    void TestStencil::OnImGuiRender() 
    {
        for (auto &item : m_ShaderMap)
            if(ImGui::RadioButton(item.first.c_str(), m_ActiveShader == item.second)) 
            {
                m_ActiveShader = item.second;
                m_Shader = std::make_unique<Shader>(m_ActiveShader);
            }
    }
}