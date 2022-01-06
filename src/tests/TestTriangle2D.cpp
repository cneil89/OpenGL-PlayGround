#include "TestTriangle2D.h"

#include "Renderer.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

    TestTriangle2D::TestTriangle2D()
        : m_Proj(glm::ortho(0.0f, 1600.0f, 0.0f, 1200.0f, -1.0f, 1.0f)),
            m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
            m_Translation(470, 280, 0)
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        float positions[] = {
            //   Positions            // Colors
            -150.0f, -150.0f, 0.0f,   1.0f, 0.0f, 0.0f,    // Bottom Left
             150.0f, -150.0f, 0.0f,   0.0f, 1.0f, 0.0f,    // Borrom Right
               0.0f,  150.0f, 0.0f,   0.0f, 0.0f, 1.0f     // Top Middle
        };

        uint32_t indicies[] = {
            0, 1, 2
        };

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 3 * 6 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, 3);
        
        m_Shader = std::make_unique<Shader>("res/shaders/FlatColor.Shader");
        m_Shader->Bind();
    }

    TestTriangle2D::~TestTriangle2D()
    {

    }

    void TestTriangle2D::OnUpdate(float deltaTime) 
    {

    }

    void TestTriangle2D::OnRender() 
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
        glm::mat4 mvp = m_Proj * m_View * model;
        
        m_VAO->Bind();
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestTriangle2D::OnImGuiRender() 
    {
        ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 1600.0f); 
    }
}