#include "defines.h"
#include "Renderer.h"
#include "Camera.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "stb/stb_image.h"

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestTriangle2D.h"
#include "tests/TestCube3D.h"
#include "tests/TestPointLight3D.h"
#include "tests/TestModel.h"
#include "tests/TestDepth.h"
#include "tests/TestStencil.h"
#include "tests/TestBlend.h"
#include "tests/TestCulling.h"
#include "tests/TestFramebuffer.h"
#include "tests/TestCubemap.h"
#include "tests/TestEnvironmentMapping.h"
#include "tests/TestAdvancedGLSL.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

const char *APP_NAME = "OpenGL Tutorial";

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    GLFWwindow *window;
    if (!glfwInit())
    {
        std::cout << "error" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    uint32_t screenWidth = mode->width;
    uint32_t screenHeight = mode->height;
    bool wireFrameEnabled = false;

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_NAME, NULL, NULL);

    {
        GLFWimage images[1];
        images[0].pixels = stbi_load("res/icons/ogl.png", &images[0].width, &images[0].height, 0, 4);
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(images[0].pixels);
    }

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    std::cout << "GFX Card Manufacturer: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GFX Card:              " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version:        " << glGetString(GL_VERSION) << std::endl;
    std::cout << "ImGui  Version:        " << ImGui::GetVersion() << std::endl;
    std::cout << "Screen Size:           " << screenWidth << "x" << screenHeight << std::endl;

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    {

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::Test *currentTest = nullptr;
        test::TestMenu *testMenu = new test::TestMenu(currentTest);
        currentTest = new test::TestAdvancedGLSL();

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
        testMenu->RegisterTest<test::TestTriangle2D>("2D Triangle");
        testMenu->RegisterTest<test::TestCube3D>("3D Cube");
        testMenu->RegisterTest<test::TestPointLight3D>("Point Light");
        testMenu->RegisterTest<test::TestModel>("Model Loading");
        testMenu->RegisterTest<test::TestDepth>("Depth Testing");
        testMenu->RegisterTest<test::TestStencil>("Stencil");
        testMenu->RegisterTest<test::TestBlend>("Blending");
        testMenu->RegisterTest<test::TestCulling>("Culling");
        testMenu->RegisterTest<test::TestFramebuffer>("Framebuffer");
        testMenu->RegisterTest<test::TestCubemap>("Cubemap");
        testMenu->RegisterTest<test::TestEnvironmentMapping>("Environment Mapping");
        testMenu->RegisterTest<test::TestAdvancedGLSL>("Advanced GLSL");

        while (!glfwWindowShouldClose(window))
        {

            if (wireFrameEnabled)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            // GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            // GLCall(glClearColor(0.033f, 0.555f, 0.667f, 1.0f));
            GLCall(glClearColor(0.255f, 0.004f, 0.522f, 1.0f));
            renderer.Clear();
            processInput(window);

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            ImGui_ImplGlfwGL3_NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender(camera);
                ImGui::Begin(currentTest->getTestName().c_str());
                if (currentTest != testMenu)
                {
                    if (ImGui::Button("<-"))
                    {
                        delete currentTest;
                        currentTest = testMenu;
                        camera.Reset();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Reset Camera"))
                        camera.Reset();
                }
                currentTest->OnImGuiRender();
                ImGui::Separator();
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::Checkbox("Wireframe", &wireFrameEnabled);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;
    }

    std::cout << "Goodbye!" << std::endl;

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    // If escape is press window will close.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // Make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y -coordinates go from bottom to top.
        camera.ProcessMouseMovement(xoffset, yoffset);

        lastX = xpos;
        lastY = ypos;
    }
    else
    {
        firstMouse = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}