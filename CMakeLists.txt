cmake_minimum_required(VERSION 3.20)

project(OpenGL-Playground VERSION 1.0.0 LANGUAGES CXX C)

#GLFW
message("GLFW CONFIGS")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW build documentation" FORCE)
add_subdirectory(vendor/glfw)

#ASSIMP
message("\nASSIMP Configs")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Assimp warnings as errors" FORCE)
add_subdirectory(vendor/assimp)

message("\n###### END VENDOR CONFIGS ######\n")

set(OGL_TEST_FILES src/tests/Test.cpp
                   src/tests/TestClearColor.cpp
                   src/tests/TestTexture2D.cpp
                   src/tests/TestTriangle2D.cpp 
                   src/tests/TestCube3D.cpp 
                   src/tests/TestPointLight3D.cpp 
                   src/tests/TestModel.cpp
                   src/test/TestDepth.cpp 
                   src/test/TestStencil.cpp 
                   src/test/TestBlend.cpp 
                   src/test/TestCulling.cpp 
                   src/test/TestFrameBuffer.cpp 
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


add_executable(${PROJECT_NAME} ${SOURCE_FILES}
                                ${OGL_TEST_FILES})               