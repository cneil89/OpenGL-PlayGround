#include "TestPointLight3D.h"

#include "Renderer.h"
#include "Camera.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace test {

// View Ports for object placement
#define MIN_VP -5.0f
#define MAX_VP  5.0f
#define MAX_PLIGHT 6

    TestPointLight3D::TestPointLight3D()
    {
        glEnable(GL_DEPTH_TEST);
        srand((uint32_t)time(NULL));

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

    void TestPointLight3D::OnRender(Camera& camera)
    {
        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f););
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);

        m_Shader->Bind();
        m_Shader->SetUniformVec3f("viewPos", camera.GetPosition());
        m_Shader->SetUniform1f("material.shininess", 32.0f);
        
        m_Shader->SetUniformVec3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
        m_Shader->SetUniformVec3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        m_Shader->SetUniformVec3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        m_Shader->SetUniformVec3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

        m_Shader->SetUniform1i("pointLightNum", m_LightPositions.size());

        for (uint32_t i = 0; i < m_LightPositions.size(); i++)
            SetPointLightProps(i);

        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        view = camera.GetViewMatrix(); 
        projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);

        m_VAO->Bind();
        for (uint32_t i = 0; i < m_CubePositions.size(); ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_CubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->SetUniformMat4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Render lightcube
        for (uint32_t i = 0; i < m_LightPositions.size(); i++)
        {
            m_LightCubeShader->Bind();
            m_LightCubeShader->SetUniformMat4f("projection", projection);
            m_LightCubeShader->SetUniformMat4f("view", view);
            glm::mat4 model(1.0f);
            model = glm::translate(model, m_LightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            m_LightCubeShader->SetUniformMat4f("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    void TestPointLight3D::OnImGuiRender()
    {
        if (ImGui::Button("Add cube"))
            GenerateCube();
        ImGui::SameLine();
        if (ImGui::Button("Add light") && m_LightPositions.size() < MAX_PLIGHT)
            m_LightPositions.push_back(glm::vec3{0.0f, 0.0f, 0.0f});
        
        for (uint32_t i = 0; i < m_LightPositions.size() && i < MAX_PLIGHT; i++)
        {
            if(ImGui::Button(("Remove##" + std::to_string(i)).c_str()))
                m_LightPositions.erase(m_LightPositions.begin() + i);
            ImGui::SameLine();
            ImGui::SliderFloat3(("Light #" + std::to_string(i)).c_str(), &m_LightPositions[i].x, MIN_VP * 2, MAX_VP * 2);
        }

        if (m_CubePositions.size() > 0)
        {
            ImGui::Begin("Cubes");
            for (uint32_t i = 0; i < m_CubePositions.size(); i++)
            {
                std::string str = "Cube #";
                str += std::to_string(i);
                const char* cubeNum = str.c_str();

                if (ImGui::Button(("Remove##" + std::to_string(i)).c_str()))
                    m_CubePositions.erase(m_CubePositions.begin() + i);
                ImGui::SameLine();
                ImGui::SliderFloat3(cubeNum, &m_CubePositions[i].x, MIN_VP, MAX_VP);
            }

            ImGui::End();
        }
    }

    void TestPointLight3D::GenerateCube()
    {
        glm::vec3 cube(randomNum(MIN_VP, MAX_VP), randomNum(MIN_VP, MAX_VP), randomNum(MIN_VP, 0.0f));

        bool exists = false;
        for (auto c : m_CubePositions)
        {
            if (cube == c)
            {
                exists = true;
                break;
            }
        }
        if (!exists)
            m_CubePositions.push_back(cube);
        else
            GenerateCube();
    }

    void TestPointLight3D::SetPointLightProps(uint32_t index)
    {
        if (index < MAX_PLIGHT)
        {
            std::string pointLight = "pointLights[";
            pointLight += std::to_string(index);
            pointLight += "]";

            m_Shader->SetUniformVec3f(pointLight + ".position", m_LightPositions[index]);
            m_Shader->SetUniformVec3f(pointLight + ".ambient",  0.2f, 0.2f, 0.2f);
            m_Shader->SetUniformVec3f(pointLight + ".diffuse",  0.5f, 0.5f, 0.5f);
            m_Shader->SetUniformVec3f(pointLight + ".specular", 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniform1f   (pointLight + ".constant",  1.0f);
            m_Shader->SetUniform1f   (pointLight + ".linear",    0.09f);
            m_Shader->SetUniform1f   (pointLight + ".quadratic", 0.032f);
        }
    }

    float TestPointLight3D::randomNum(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> dis(min, max);
        return (float)dis(gen);
    }
}