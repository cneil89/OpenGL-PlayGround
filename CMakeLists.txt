cmake_minimum_required(VERSION 3.20)

project(OpenGL-Playground VERSION 1.0.0 LANGUAGES CXX C)

#GLFW
message("GLFW CONFIGS")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW build documentation" FORCE)
add_subdirectory(vendor/GLFW)

#ASSIMP
message("\nASSIMP Configs")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Assimp warnings as errors" FORCE)
add_subdirectory(vendor/assimp)

#GLEW
message("\nFinding OpenGL")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

message("\n###### END VENDOR CONFIGS ######\n")

set(OGL_TEST_FILES src/tests/Test.cpp
                   src/tests/TestClearColor.cpp
                   src/tests/TestTexture2D.cpp
                   src/tests/TestTriangle2D.cpp 
                   src/tests/TestCube3D.cpp 
                   src/tests/TestPointLight3D.cpp 
                   src/tests/TestModel.cpp
                   src/tests/TestDepth.cpp 
                   src/tests/TestStencil.cpp 
                   src/tests/TestBlend.cpp 
                   src/tests/TestCulling.cpp 
                   src/tests/TestFrameBuffer.cpp 
                   src/tests/TestCubemap.cpp 
                   src/tests/TestEnvironmentMapping.cpp 
                   src/tests/TestAdvancedGLSL.cpp)

 set(SOURCE_FILES src/main.cpp
                   src/VertexBuffer.cpp
                   src/VertexArray.cpp
                   src/Texture.cpp
                   src/stb_image.cpp
                   src/Shader.cpp
                   src/Renderer.cpp
                   src/Model.cpp
                   src/Mesh.cpp
                   src/IndexBuffer.cpp
                   src/Camera.cpp)
                 
set(IMGUI_FILES vendor/imgui/include/imgui/imgui_demo.cpp
                 vendor/imgui/include/imgui/imgui_draw.cpp
                 vendor/imgui/include/imgui/imgui_impl_glfw_gl3.cpp
                 vendor/imgui/include/imgui/imgui.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES}
                 ${OGL_TEST_FILES}
                 ${IMGUI_FILES})
                 
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/GLFW/include)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/GLEW/include)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/stb_image/include)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/imgui/include)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/assimp/include)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} assimp)