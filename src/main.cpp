#include "defines.h"

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int main()
{
    const char* appName = "OpenGL Tutorial";
    bool fullscreen = false;
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "error" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    uint32_t screenWidth = mode->width;
    uint32_t screenHeight = mode->height;

    std::cout << "Screen Size: " << mode->width << "x"<< mode->height << std::endl;

    uint8_t choice = '0';
    do
    {
        std::cout << "Would you like to try full screen? (y/n): ";
        std::cin >> choice;   
    } while (choice != 'y' && choice != 'n');
    
    if (choice == 'n')
    {
        screenWidth = 960;
        screenHeight = 540;
        monitor = NULL;
    }

    window = glfwCreateWindow(screenWidth, screenHeight, appName, monitor, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    std::cout << "\nOpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    {
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        //                           * floats per vertex * size of float
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        
        Texture texture("res/textures/cute-dalmatian-sitting-cya.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Shader shader2("res/shaders/Flashy.shader");
        float positions2[] = { /*x,y*/
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };
        VertexArray va2;
        VertexBuffer vb2(positions2, 4 * 4 * sizeof(float));
        VertexBufferLayout layout2;
        layout2.Push<float>(2);
        layout2.Push<float>(2);
        va2.AddBuffer(vb2, layout2);
        IndexBuffer ib2(indices, 6);

        Renderer renderer;

        float r = 0.0f;
        float g = 0.2f;
        float b = 0.5f;
        float a = 1.0f;
        float rincrement  = 0.05f;
        float gincrement  = 0.01f;
        float bincrement  = 0.03f;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);

        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);
        glm::vec3 translationC(100, 200, 0);

        double xpos, ypos;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
        
            {    
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                
                renderer.Draw(va, ib, shader);
            }
            {    
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                
                renderer.Draw(va, ib, shader);
            }
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationC);
                glm::mat4 mvp = proj * view * model;

                shader2.Bind();
                shader2.SetUniformMat4f("u_MVP", mvp);
                shader2.SetUniform4f("u_Color", r, g, b, a);

                renderer.Draw(va2, ib2, shader2);
            }



            // glfwGetCursorPos(window, &xpos, &ypos);
            // std::cout << "X: [" << xpos << "], Y: [" << ypos << "]" << std:: endl;

            {
                ImGui::Begin("Fun Sliders");
                ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, (float)screenWidth);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, (float)screenWidth);            // Edit 1 float using a slider from 0.0f to 1.0f    

                ImGui::NewLine();
                ImGui::Separator();
                ImGui::SliderFloat3("Translation C", &translationC.x, 0.0f, (float)screenWidth);
                ImGui::SliderFloat("R Value", &r, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::SliderFloat("G Value", &g, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::SliderFloat("B Value", &b, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
                ImGui::SliderFloat("A Value", &a, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f 

                ImGui::NewLine();
                ImGui::Separator();   
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }


    std::cout << "Goodbye!" << std::endl;

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}