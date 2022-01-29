#include "TestPointLight3D.h"

#include "Renderer.h"
#include "Camera.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace test {


    TestPointLight3D::TestPointLight3D()
        : m_LightPos(0.5f, 0.5f, 0.0f)
    {
        glEnable(GL_DEPTH_TEST);

        float vertices[] = {
            // positions                // normals                 // texture coords
            -0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,        0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,        1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,        1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,        1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,        0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,        0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,        0.0f,  0.0f,  1.0f,        0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,        0.0f,  0.0f,  1.0f,        1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,        0.0f,  0.0f,  1.0f,        1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,        0.0f,  0.0f,  1.0f,        1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,        0.0f,  0.0f,  1.0f,        0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,        0.0f,  0.0f,  1.0f,        0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f,       -1.0f,  0.0f,  0.0f,        1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,       -1.0f,  0.0f,  0.0f,        1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,       -1.0f,  0.0f,  0.0f,        0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,       -1.0f,  0.0f,  0.0f,        0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,       -1.0f,  0.0f,  0.0f,        0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,       -1.0f,  0.0f,  0.0f,        1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,        1.0f,  0.0f,  0.0f,        1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,        1.0f,  0.0f,  0.0f,        1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,        1.0f,  0.0f,  0.0f,        0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,        1.0f,  0.0f,  0.0f,        0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,        1.0f,  0.0f,  0.0f,        0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,        1.0f,  0.0f,  0.0f,        1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,        0.0f, -1.0f,  0.0f,        0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,        0.0f, -1.0f,  0.0f,        1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,        0.0f, -1.0f,  0.0f,        1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,        0.0f, -1.0f,  0.0f,        1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,        0.0f, -1.0f,  0.0f,        0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,        0.0f, -1.0f,  0.0f,        0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,        0.0f,  1.0f,  0.0f,        0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,        0.0f,  1.0f,  0.0f,        1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,        0.0f,  1.0f,  0.0f,        1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,        0.0f,  1.0f,  0.0f,        1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,        0.0f,  1.0f,  0.0f,        0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,        0.0f,  1.0f,  0.0f,        0.0f,  1.0f
        };


        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 36 * 8 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_LightVAO = std::make_unique<VertexArray>();
        m_LightVAO->AddBuffer(*m_VertexBuffer, layout);

        m_Shader = std::make_unique<Shader>("res/shaders/OGLBookPointShader.shader");
        m_LightCubeShader = std::make_unique<Shader>("res/shaders/OGLBookLightCube.shader");
        m_Texture1 = std::make_unique<Texture>("res/textures/container2.png", false);
        m_Texture2 = std::make_unique<Texture>("res/textures/container2_specular.png", false);
        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        m_Shader->SetUniform1i("material.diffuse", 0);
        m_Shader->SetUniform1i("material.specular", 1);

    }

    TestPointLight3D::~TestPointLight3D () 
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestPointLight3D::OnUpdate(float deltaTime) 
    {

    }

    void TestPointLight3D::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f););
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glm::vec3 m_CubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f),
            glm::vec3( 0.5f, -4.3f, -9.0f)
        };

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);
        m_Shader->Bind();
        m_Shader->SetUniformVec3f("light.position", m_LightPos);
        m_Shader->SetUniformVec3f("viewPos", 0.0f, 0.0f, -3.0f);
        
        // Light Properties
        m_Shader->SetUniformVec3f("light.ambient",  0.2f, 0.2f, 0.2f);
        m_Shader->SetUniformVec3f("light.diffuse",  0.5f, 0.5f, 0.5f);
        m_Shader->SetUniformVec3f("light.specular", 1.0f, 1.0f, 1.0f);

        m_Shader->SetUniform1f("light.constant",  1.0f);
        m_Shader->SetUniform1f("light.linear",    0.09f);
        m_Shader->SetUniform1f("light.quadratic", 0.032f);

        // Material Properties
        m_Shader->SetUniform1f("material.shininess", 32.0f);

        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);

        m_VAO->Bind();
        for (uint32_t i = 0; i < 11; ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_CubePositions[i]);
            float angle = 20.0f * i;
            if (angle == 0)
                angle = 10.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->SetUniformMat4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Render lightcube
        m_LightCubeShader->Bind();
        m_LightCubeShader->SetUniformMat4f("projection", projection);
        m_LightCubeShader->SetUniformMat4f("view", view);
        glm::mat4 model(1.0f);
        model = glm::translate(model, m_LightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        m_LightCubeShader->SetUniformMat4f("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void TestPointLight3D::OnImGuiRender()
    {
        ImGui::SliderFloat3("Light Position", &m_LightPos.x, -10.0f, 10.0f);
    }
}