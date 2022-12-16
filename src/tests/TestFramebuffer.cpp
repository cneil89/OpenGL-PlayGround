#include "TestFramebuffer.h"

#include "imgui/imgui.h"

namespace test {

    TestFramebuffer::TestFramebuffer()
        : Test("Framebuffer")
    {

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

    /*
        Remember: to specify vertices in a counter-clockwise winding order you need to visualize the triangle
        as if you're in front of the triangle and from that point of view, is where you set their order.
        
        To define the order of a triangle on the right side of the cube for example, you'd imagine yourself looking
        straight at the right side of the cube, and then visualize the triangle and make sure their order is specified
        in a counter-clockwise order. This takes some practice, but try visualizing this yourself and see that this
        is correct.
    */

    float cubeVertices[] = {
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
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
        m_CubeTexture = std::make_unique<Texture>("res/textures/brickwall.jpg");
        m_CubeTexture->Bind(0);

    }

    TestFramebuffer::~TestFramebuffer()
    {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }

    void TestFramebuffer::OnUpdate(float deltaTime) 
    {

    }

    void TestFramebuffer::OnRender(Camera& camera) 
    {
        glClearColor(0.255f, 0.004f, 0.522f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_CubeTexture->Bind(0);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);

        m_CubeVAO->Bind();
        m_Shader->SetUniform1i("texture1", 0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        m_Shader->SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void TestFramebuffer::OnImGuiRender() 
    {
    }
}