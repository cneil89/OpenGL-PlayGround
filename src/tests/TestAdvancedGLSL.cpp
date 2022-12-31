#include "TestAdvancedGLSL.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "glm/gtc/type_ptr.hpp"

namespace test
{
	TestAdvancedGLSL::TestAdvancedGLSL()
		: Test("Advanced GLSL")
	{
        glEnable(GL_DEPTH_TEST);
        float cubeVertices[] = {
            // positions         
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
        };

        m_ShaderRed = std::make_unique<Shader>("res/shaders/AdvancedGLSL-Red.shader");
        m_ShaderGreen = std::make_unique<Shader>("res/shaders/AdvancedGLSL-Green.shader");
        m_ShaderBlue = std::make_unique<Shader>("res/shaders/AdvancedGLSL-Blue.shader");
        m_ShaderYellow = std::make_unique<Shader>("res/shaders/AdvancedGLSL-Yellow.shader");
        m_CubeVAO = std::make_unique<VertexArray>();
        m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 3 * sizeof(float));
        VertexBufferLayout cubeLayout;
        cubeLayout.Push<float>(3);
        m_CubeVAO->AddBuffer(*m_CubeVBO, cubeLayout);
        m_ShaderRed->Bind();
        m_ShaderGreen->Bind();
        m_ShaderBlue->Bind();
        m_ShaderYellow->Bind();


        // Uniform Buffer
        /**
         * TODO: Abstract.
         */

        uint32_t red = glGetUniformBlockIndex(m_ShaderRed->GetID(), "Matrices");
        uint32_t green = glGetUniformBlockIndex(m_ShaderGreen->GetID(), "Matrices");
        uint32_t blue = glGetUniformBlockIndex(m_ShaderBlue->GetID(), "Matrices");
        uint32_t yellow = glGetUniformBlockIndex(m_ShaderYellow->GetID(), "Matrices");

        GLCall(glUniformBlockBinding(m_ShaderRed->GetID(), red, 0));
        GLCall(glUniformBlockBinding(m_ShaderGreen->GetID(), green, 0));
        GLCall(glUniformBlockBinding(m_ShaderBlue->GetID(), blue, 0));
        GLCall(glUniformBlockBinding(m_ShaderYellow->GetID(), yellow, 0));

        GLCall(glGenBuffers(1, &m_UBOMatrices));
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_UBOMatrices));
        GLCall(glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW));
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));

        GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_UBOMatrices, 0, 2 * sizeof(glm::mat4)));

	}

	TestAdvancedGLSL::~TestAdvancedGLSL()
	{
        glDisable(GL_DEPTH_TEST);
	}

	void TestAdvancedGLSL::OnUpdate(float deltaTime)
	{

	}

	void TestAdvancedGLSL::OnRender(Camera& camera)
	{
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer renderer;

        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_UBOMatrices));
        GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection)));
        glm::mat4 view = camera.GetViewMatrix();
        GLCall(glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view)));
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));

        m_CubeVAO->Bind();
        m_ShaderRed->Bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f));
        m_ShaderRed->SetUniformMat4f("model", model);
        renderer.Draw(*m_CubeVAO, *m_ShaderRed, 36);

        m_ShaderGreen->Bind();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));
        m_ShaderGreen->SetUniformMat4f("model", model);
        renderer.Draw(*m_CubeVAO, *m_ShaderGreen, 36);

        m_ShaderBlue->Bind();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));
        m_ShaderBlue->SetUniformMat4f("model", model);
        renderer.Draw(*m_CubeVAO, *m_ShaderBlue, 36);

        m_ShaderYellow->Bind();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));
        m_ShaderYellow->SetUniformMat4f("model", model);
        renderer.Draw(*m_CubeVAO, *m_ShaderYellow, 36);


	}

	void TestAdvancedGLSL::OnImGuiRender()
	{

	}

}
