#pragma once
#include "defines.h"
#include "Renderer.h"

class Texture
{
private:
    uint32_t m_RendererID;
    std::string m_FilePath;
    uint8_t* m_LocalBuffer;
    int32_t m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path, bool alpha = true);
    ~Texture();

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    inline uint32_t getWidth() const { return m_Width; }
    inline uint32_t getHeight() const { return m_Height; }
};