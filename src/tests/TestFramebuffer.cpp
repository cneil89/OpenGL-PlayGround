#include "TestFramebuffer.h"

#include "imgui/imgui.h"

namespace test {

    TestFramebuffer::TestFramebuffer()
        : Test("Framebuffer")
    {

        glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LESS);

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
        float planeVertices[] = {
            // positions             // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,     2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,     0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,     0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,     2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,     0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,     2.0f, 2.0f								
        };
        float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
             0.75f, -0.75f,  1.0f, 0.0f,
            -0.75f,  0.75f,  0.0f, 1.0f,
            -0.75f, -0.75f,  0.0f, 0.0f,

             0.75f, -0.75f,  1.0f, 0.0f,
            -0.75f,  0.75f,  0.0f, 1.0f,
             0.75f,  0.75f,  1.0f, 1.0f
        };

        m_ShaderMap["Blending"] = "res/shaders/OGLBookBlending.shader";

        m_ActiveShader = m_ShaderMap["Blending"];
        m_Shader = std::make_unique<Shader>(m_ActiveShader);
        m_ScreenShader = std::make_unique<Shader>("res/shaders/OGLBookScreen.shader");

        m_Shader->Bind();
        m_Shader->SetUniform1i("texture1", 0);
        m_ScreenShader->Bind();
        
        //CUBE
        m_CubeVAO = std::make_unique<VertexArray>();
        m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float));
        VertexBufferLayout CubeLayout;
        CubeLayout.Push<float>(3);
        CubeLayout.Push<float>(2);
        m_CubeVAO->AddBuffer(*m_CubeVBO, CubeLayout);
        m_CubeTexture = std::make_unique<Texture>("res/textures/container.jpg");
        m_CubeTexture->Bind(0);

        //PLANE
        m_PlaneVAO = std::make_unique<VertexArray>();
        m_PlaneVBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 5 * sizeof(float));
        VertexBufferLayout PlaneLayout;
        PlaneLayout.Push<float>(3);
        PlaneLayout.Push<float>(2);
        m_PlaneVAO->AddBuffer(*m_PlaneVBO, PlaneLayout);
        m_PlaneTexture = std::make_unique<Texture>("res/textures/metal.png");
        m_PlaneTexture->Bind(1);

        //QUAD
        m_QuadVAO = std::make_unique<VertexArray>();
        m_QuadVBO = std::make_unique<VertexBuffer>(quadVertices, 6 * 4 * sizeof(float));
        VertexBufferLayout QuadLayout;
        QuadLayout.Push<float>(2);
        QuadLayout.Push<float>(2);
        m_QuadVAO->AddBuffer(*m_QuadVBO, QuadLayout);



        /*
         * TODO: Part these into classes. 
         */
        
        glGenFramebuffers(1, &m_Fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);

        glGenTextures(1, &m_Tcb);
        glBindTexture(GL_TEXTURE_2D, m_Tcb);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Tcb, 0);

        glGenRenderbuffers(1, &m_Rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_Rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Rbo);
        m_ScreenShader->SetUniform1i("screenTexture", 1);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
        Renderer renderer;

        glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_CubeTexture->Bind(0);
        m_PlaneTexture->Bind(1);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("view", view);
        m_Shader->SetUniformMat4f("projection", projection);

        m_Shader->SetUniform1i("texture1", 0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        m_Shader->SetUniformMat4f("model", model);
        renderer.Draw(*m_CubeVAO, *m_Shader, 36);

        model = glm::translate(model, glm::vec3(1.5f, 0.0f, -1.5f));
        m_Shader->SetUniformMat4f("model", model);
        renderer.Draw(*m_CubeVAO, *m_Shader, 36);

        m_Shader->SetUniform1i("texture1", 1);
        m_Shader->SetUniformMat4f("model", glm::mat4(1.0f));
        renderer.Draw(*m_PlaneVAO, *m_Shader, 6);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // // clear all relevant buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);


        glBindTexture(GL_TEXTURE_2D, m_Tcb);	// use the color attachment texture as the texture of the quad plane
        renderer.Draw(*m_QuadVAO, *m_ScreenShader, 6);


    }

    void TestFramebuffer::OnImGuiRender() 
    {
    }
}