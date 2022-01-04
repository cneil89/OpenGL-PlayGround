#pragma once
#include "defines.h"
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
    uint32_t m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};