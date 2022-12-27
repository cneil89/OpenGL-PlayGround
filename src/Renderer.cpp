#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char *function, const char *file, uint32_t line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

/**
 * @brief Draw the vertexarray.
 *
 * @param va
 * @param shader
 * @param size number of vertex's
 */
void Renderer::Draw(const VertexArray &va, const Shader &shader, const uint32_t size) const
{
    shader.Bind();
    va.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
}