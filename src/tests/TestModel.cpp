#include "TestModel.h"

#include "Renderer.h"
#include "Camera.h"


namespace test {

    TestModel::TestModel()
    {

    }

    TestModel::~TestModel()
    {

    }

    void TestModel::OnUpdate(float deltaTime) 
    {

    }

    void TestModel::OnRender(Camera& camera)
    {
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    }

    void TestModel::OnImGuiRender()
    {

    }
}