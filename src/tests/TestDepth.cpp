#include "TestDepth.h"

namespace test {

    TestDepth::TestDepth()
    {
        float cubeVertices[] = {
            // positions             // texture Coords
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f
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
    }

    TestDepth::~TestDepth()
    {

    }

    void TestDepth::OnUpdate(float deltaTime) 
    {

    }

    void TestDepth::OnRender(Camera& camera) 
    {

    }

    void TestDepth::OnImGuiRender() 
    {

    }
}