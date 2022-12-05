#include "TestModel.h"

#include "Renderer.h"
#include "Camera.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>


namespace test {

    TestModel::TestModel()
        : Test("Model"), m_Model("res/models/backpack/backpack.obj")
        // : m_Model("res/models/donut/donut.obj")
        // : m_Model("res/models/cubes/cubes.obj")
    {
        glEnable(GL_DEPTH_TEST);
        m_Shader = std::make_unique<Shader>("res/shaders/OGLBookPointShader.shader");
        m_LightCubeShader = std::make_unique<Shader>("res/shaders/OGLBookLightCube.shader");
    }

    TestModel::~TestModel()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestModel::OnUpdate(float deltaTime) 
    {

    }

    void TestModel::OnRender(Camera& camera)
    {
        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        m_Shader->Bind();

        // Lighting
        //  Directional Light
        m_Shader->SetUniformVec3f("viewPos", camera.GetPosition());
        m_Shader->SetUniform1f("material.shininess", 32.0f);
        
        m_Shader->SetUniformVec3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
        m_Shader->SetUniformVec3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        m_Shader->SetUniformVec3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        m_Shader->SetUniformVec3f("dirLight.specular", 0.5f, 0.5f, 0.5f);

        // Point Lightining
        m_Shader->SetUniform1i("pointLightNum", m_LightPositions.size());
        for (uint32_t i = 0; i < m_LightPositions.size(); i++)
            SetPointLightProps(i);
    

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        m_Shader->SetUniformMat4f("projection", projection);
        m_Shader->SetUniformMat4f("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.5f));	// it's a bit too big for our scene, so scale it down
        m_Shader->SetUniformMat4f("model", model);

        m_Model.Draw(*m_Shader);

    }

    void TestModel::OnImGuiRender()
    {
        if (ImGui::Button("Add light") && m_LightPositions.size() < 2)
            m_LightPositions.push_back(glm::vec3{0.0f, 0.0f, 0.0f});
        
        ImGui::SameLine();
        ImGui::Text("Max 2 Lights");

        for (uint32_t i = 0; i < m_LightPositions.size(); i++)
        {
            ImGui::PushID(i);
            if(ImGui::Button("Remove"))
                m_LightPositions.erase(m_LightPositions.begin() + i);
            ImGui::SameLine();
            ImGui::SliderFloat3(("Light"), &m_LightPositions[i].x, MIN_VP * 2, MAX_VP * 2);
            ImGui::PopID();
        }
    }

    void TestModel::SetPointLightProps(uint32_t index)
    {
        if (index < MAX_PLIGHT)
        {
            std::string pointLight = "pointLights[";
            pointLight += std::to_string(index);
            pointLight += "]";

            m_Shader->SetUniformVec3f(pointLight + ".position",  m_LightPositions[index]);
            m_Shader->SetUniformVec3f(pointLight + ".ambient",   0.2f, 0.2f, 0.2f);
            m_Shader->SetUniformVec3f(pointLight + ".diffuse",   0.5f, 0.5f, 0.5f);
            m_Shader->SetUniformVec3f(pointLight + ".specular",  1.0f, 1.0f, 1.0f);
            m_Shader->SetUniform1f   (pointLight + ".constant",  1.0f);
            m_Shader->SetUniform1f   (pointLight + ".linear",    0.09f);
            m_Shader->SetUniform1f   (pointLight + ".quadratic", 0.032f);
        }
    }
}