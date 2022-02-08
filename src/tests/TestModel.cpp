#include "TestModel.h"

#include "Renderer.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace test {

    TestModel::TestModel()
        : m_Model("res/models/backpack/backpack.obj")
    {
        glEnable(GL_DEPTH_TEST);
        // m_Model = std::make_unique<Model>("res/models/backpack/backpack.obj");
        m_Shader = std::make_unique<Shader>("res/shaders/OGLBookModelLoading.shader");
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
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        m_Shader->Bind();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        m_Shader->SetUniformMat4f("projection", projection);
        m_Shader->SetUniformMat4f("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        m_Shader->SetUniformMat4f("model", model);

        m_Model.Draw(*m_Shader);

    }

    void TestModel::OnImGuiRender()
    {

    }
}